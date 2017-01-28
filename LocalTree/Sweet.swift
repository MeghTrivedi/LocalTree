//
//  Sweet.swift
//  LocalTree
//
//  Created by Megh Trivedi on 2017-01-11.
//  Copyright © 2017 Megh Trivedi. All rights reserved.
//

import Foundation
import FirebaseDatabase

struct Sweet {
    
    let key:String!
    let content:String!
    let addedByUser:String!
    let itemRef:FIRDatabaseReference?
    
    init (content:String, addedByUser:String, key:String = ""){
        self.key = key
        self.content = content
        self.addedByUser = addedByUser
        self.itemRef = nil
    }
    
    init (snapshot:FIRDataSnapshot) {
        key = snapshot.key
        itemRef = snapshot.ref
        
        if let dict = snapshot.value as? NSDictionary, let sweetContent = dict["content"] as? String{
            content = sweetContent
        }else {
            content = ""
        }
        
        if let dict = snapshot.value as? NSDictionary, let sweetUser = dict["addedByUser"] as? String{
            addedByUser = sweetUser
        }else {
            addedByUser = ""
        }
    }
    
    func toAnyObject() -> Any {
        
        return["content":content, "addedByUser":addedByUser]
    
    }
}
