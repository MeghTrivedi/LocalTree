//
//  User.swift
//  LocalTree
//
//  Created by Megh Trivedi on 2017-01-11.
//  Copyright © 2017 Megh Trivedi. All rights reserved.
//

import Foundation
import FirebaseAuth

struct User{
    let uid:String
    let email:String
    
    init(userData:FIRUser) {
        uid = userData.uid
        
        if let mail = userData.providerData.first?.email {
            email = mail
        }else{
            email = ""
        }
    }
    init(uid:String, email:String) {
        self.uid = uid
        self.email = email
    }
}
