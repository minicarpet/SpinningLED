//
//  ViewController.swift
//  spinning Led
//
//  Created by Logan Gallois on 25/09/2016.
//  Copyright © 2016 Logan Gallois. All rights reserved.
//

import UIKit
import CoreBluetooth

let Modes = [
    "fullAuto",
    "ledAuto",
    "motAuto",
    "motAuto"
]

class ViewController: UIViewController, CBCentralManagerDelegate, CBPeripheralDelegate, UIPickerViewDelegate, UIPickerViewDataSource {
    
    @IBOutlet var modeSelect: UITextField!
    let CM = CBCentralManager()
    var myPeripheral: CBPeripheral?
    var RxCarac: CBCharacteristic?

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        CM.delegate = self
        let PickerView = UIPickerView()
        let toolBar = UIToolbar(frame: CGRect(origin: CGPoint(x: 0, y: 0), size: CGSize(width: self.view.frame.width, height: 50)))
        let Button = UIBarButtonItem(title: "Ok", style: .done, target: self, action: #selector(self.validate))
        let flexibleSpace = UIBarButtonItem(barButtonSystemItem: .flexibleSpace, target: self, action: nil)
        toolBar.setItems([flexibleSpace, Button, flexibleSpace], animated: false)
        toolBar.barStyle = .default
        toolBar.isUserInteractionEnabled = true
        toolBar.isTranslucent = true
        toolBar.sizeToFit()
        
        PickerView.dataSource = self
        PickerView.delegate = self
        modeSelect.inputView = PickerView
        modeSelect.inputAccessoryView = toolBar
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func validate() {
        if modeSelect.isEditing {
            modeSelect.resignFirstResponder()
        }
    }
    
    @IBAction func brightnessChange(_ sender: UISlider) {
        myPeripheral?.writeValue(("Brightness" + String(Int(sender.value))).data(using: String.Encoding.ascii)!, for: RxCarac!, type: .withResponse)
    }
    
    @IBAction func colorChange(_ sender: UISlider) {
        myPeripheral?.writeValue(("Color" + String(Int(sender.value))).data(using: String.Encoding.ascii)!, for: RxCarac!, type: .withResponse)
    }
    
    @IBAction func onLed(_ sender: UISwitch) {
        myPeripheral?.writeValue(("onLed" + String(sender.isOn)).data(using: String.Encoding.ascii)!, for: RxCarac!, type: .withResponse)
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return Modes.count
    }
    
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return Modes[row]
    }
    
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        modeSelect.text = Modes[row]
    }
    
    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        if central.state.rawValue == 4 {
            // BLE IS OFF
            let AlertMessage = UIAlertController(title: "Bluetooth désactivé", message: "Merci d'activer le Bluetooth", preferredStyle: .alert)
            let ActionAlert = UIAlertAction(title: "Ok", style: .default) { (action) in }
            AlertMessage.addAction(ActionAlert)
            self.present(AlertMessage, animated: true, completion: nil)
        }
        if central.state.rawValue == 5 {
            // BLE IS ON
            CM.scanForPeripherals(withServices: nil, options: [CBCentralManagerScanOptionAllowDuplicatesKey: false])
        }
    }
    
    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
        print(peripheral.name)
        if peripheral.name == "SpinningLED" {
            myPeripheral = peripheral
            CM.connect(myPeripheral!, options: nil)
            CM.stopScan()
        }
    }
    
    func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
        myPeripheral = peripheral
        myPeripheral?.delegate = self
        myPeripheral?.discoverServices(nil)
        let AlertBLE = UIAlertController()
        AlertBLE.title = "Arduino trouvée"
        AlertBLE.message = "Nous avons réussi a nous connecter"
        AlertBLE.addAction(UIAlertAction(title: "Ok", style: .default, handler: nil))
        self.present(AlertBLE, animated: true, completion: nil)
    }
    
    func centralManager(_ central: CBCentralManager, didFailToConnect peripheral: CBPeripheral, error: Error?) {
        let AlertBLE = UIAlertController()
        AlertBLE.title = "Arduino trouvée"
        AlertBLE.message = "Mais nous n'avons pas réussi a nous connecter.\n Merci de relancer l'application"
        if AlertBLE.actions.count == 0 {
            AlertBLE.addAction(UIAlertAction(title: "Ok", style: .default, handler: nil))
        }
        self.present(AlertBLE, animated: true, completion: nil)
    }
    
    func centralManager(_ central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: Error?) {
        myPeripheral?.delegate = nil
        CM.connect(peripheral, options: nil)
        let AlertBLE = UIAlertController()
        AlertBLE.title = "Arduino perdue"
        AlertBLE.message = "Nous avons perdu la connexion avec l'Arduino"
        AlertBLE.addAction(UIAlertAction(title: "Ok", style: .default, handler: nil))
        self.present(AlertBLE, animated: true, completion: nil)
    }
    
    func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
        if error == nil {
            for service in peripheral.services! {
                peripheral.discoverCharacteristics(nil, for: service)
            }
        }
    }
    
    func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {
        if error == nil {
            for carac in service.characteristics! {
                RxCarac = carac
            }
        }
    }

}

