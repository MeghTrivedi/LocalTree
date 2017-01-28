//
//  SweetsTableViewController.swift
//  LocalTree
//
//  Created by Megh Trivedi on 2017-01-11.
//  Copyright © 2017 Megh Trivedi. All rights reserved.
//

import UIKit
import FirebaseDatabase
import FirebaseAuth

class SweetsTableViewController: UITableViewController {
    
    var dbRef:FIRDatabaseReference!
    var sweets = [Sweet]()

    override func viewDidLoad() {
        super.viewDidLoad()
        dbRef = FIRDatabase.database().reference().child("sweet-items")
        startObservingDB()
        
    }
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        
        FIRAuth.auth()?.addStateDidChangeListener({ (auth:FIRAuth, user:FIRUser?) in
            if let user = user {
                print("Welcome \(user.email)")
                self.startObservingDB()
            }else{
                print("Please Create an Account")
            }
        })
    }
    
    @IBAction func loginAndSignUp(_ sender: Any) {
        let userAlert = UIAlertController(title: "Login", message: "Enter Email and Password", preferredStyle: .alert)
        userAlert.addTextField { (textfield:UITextField) in
            textfield.placeholder = "Email"
        }
        userAlert.addTextField { (textfield:UITextField) in
            textfield.isSecureTextEntry = true
            textfield.placeholder = "Password"
        }
        userAlert.addAction(UIAlertAction(title: "Sign in", style: .default, handler: { (action:UIAlertAction) in
            let emailTextField = userAlert.textFields?.first!
            let passwordTextField = userAlert.textFields?.last!
            
            FIRAuth.auth()?.signIn(withEmail: (emailTextField?.text)!, password: (passwordTextField?.text)!, completion: { (user:FIRUser?, error:Error?) in
                if error != nil {
                    print(error.debugDescription)
                }
            })
        }))
        
        userAlert.addAction(UIAlertAction(title: "Sign up", style: .default, handler: { (action:UIAlertAction) in
            let emailTextField = userAlert.textFields?.first!
            let passwordTextField = userAlert.textFields?.last!
            
            FIRAuth.auth()?.createUser(withEmail: (emailTextField?.text)!, password: (passwordTextField?.text)!, completion: { (user:FIRUser?, error:Error?) in
                if error != nil {
                    print(error.debugDescription)
                }
            })
        }))
        
        self.present(userAlert, animated: true, completion: nil)
        
    }
    
    func startObservingDB () {
        dbRef.observe(.value, with: { (snapshot:FIRDataSnapshot) in
            var newSweets = [Sweet]()
            
            for sweet in snapshot.children{
                let sweetObject = Sweet(snapshot: sweet as! FIRDataSnapshot)
                newSweets.append(sweetObject)
            }
            
            self.sweets = newSweets
            self.tableView.reloadData()
            
            
        }) { (error:Error) in
            print(error.localizedDescription)
        }
    }

    @IBAction func addSweet(_ sender: Any) {
        
        let sweetAlert = UIAlertController(title: "New Add", message: "Enter Your Ad", preferredStyle: .alert)
        sweetAlert.addTextField { (textField:UITextField) in
            textField.placeholder = "Your Ad"
        }
        sweetAlert.addAction(UIAlertAction(title: "Send", style: .default, handler: { (action:UIAlertAction) in
            
            if let sweetContent = sweetAlert.textFields?.first?.text {
                let sweet = Sweet(content: sweetContent, addedByUser: "MeghTrivedi")
                
                let sweetRef = self.dbRef.child(sweetContent.lowercased())
                
                sweetRef.setValue(sweet.toAnyObject())
                
            }
        }))
        
        self.present(sweetAlert, animated: true, completion: nil)
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    // MARK: - Table view data source

    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return sweets.count
    }

 
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "Cell", for: indexPath)

        let sweet = sweets[indexPath.row]
        

        cell.textLabel?.text = sweet.content
        cell.detailTextLabel?.text = sweet.addedByUser

        return cell
    }
    
    override func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCellEditingStyle, forRowAt indexPath: IndexPath) {
        if editingStyle == .delete {
            let sweet = sweets[indexPath.row]
            sweet.itemRef?.removeValue() 
        }
    }
    
}

