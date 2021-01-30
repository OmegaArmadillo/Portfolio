package com.example.paymentcalculator

fun calculatePerPersonTotal(amount : Float, people : Int, tip : Int) : Float {

    val tipNumber = "%.2f".format(amount * (tip / 100.00))
    val tipAndTotal = "%.2f".format(amount + tipNumber.toFloat())
    val totalPerPerson = (tipAndTotal.toFloat() / people.toFloat())

    return totalPerPerson
}
