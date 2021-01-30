package com.example.accounttest2

import java.io.Serializable

class GameResult : Serializable{

    var id: Int? = null
    var player: String? = null
    var rounds: Int? = null
    var difficulty: String? = null
    var account: String? = null

    constructor(id: Int, player: String, rounds: Int, difficulty: String, account: String) {
        this.id = id
        this.player = player
        this.rounds = rounds
        this.difficulty = difficulty
        this.account = account
    }

    constructor(player: String, rounds: Int, difficulty: String, account: String) {
        this.player = player
        this.rounds = rounds
        this.difficulty = difficulty
        this.account = account
    }

}