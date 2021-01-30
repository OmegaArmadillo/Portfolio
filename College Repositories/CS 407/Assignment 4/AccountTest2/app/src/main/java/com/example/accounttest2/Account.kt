package com.example.accounttest2

import java.io.Serializable

class Account : Serializable{

    var id: Int? = null
    var accountName: String? = null
    var password: String? = null


    constructor(id: Int, accountName: String?, password: String) {
        this.id = id
        this.accountName = accountName
        this.password = password

    }

    constructor(accountName: String?, password: String) {
        this.accountName = accountName
        this.password = password
    }

}