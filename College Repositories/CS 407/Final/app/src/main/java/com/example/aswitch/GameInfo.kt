package com.example.aswitch

import java.io.Serializable

class GameInfo (val roundsSucceded: Int, val roundTime : Float, val difficulty : String, val failedCurrentRound: Boolean, val roundsFailed : Int, val failMaximum : Int, val lastGame: Int) : Serializable{
}