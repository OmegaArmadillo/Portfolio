package com.example.aswitch.database

import java.io.Serializable

class GameResult : Serializable{

        var id: Int? = null
        var player: String? = null
        var rounds: Int? = null
        var difficulty: String? = null

        constructor(id: Int, player: String, rounds: Int, difficulty: String) {
            this.id = id
            this.player = player
            this.rounds = rounds
            this.difficulty = difficulty
        }

    constructor(player: String, rounds: Int, difficulty: String) {
        this.player = player
        this.rounds = rounds
        this.difficulty = difficulty
    }

}