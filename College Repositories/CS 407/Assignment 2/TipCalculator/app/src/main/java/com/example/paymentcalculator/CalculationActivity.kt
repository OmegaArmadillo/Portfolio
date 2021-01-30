package com.example.paymentcalculator

import android.os.Bundle
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity

class CalculationActivity : AppCompatActivity(){

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_calcuation)


        var paymentInfo: PaymentInfo? = null

        val bundle : Bundle? = intent.extras

        bundle?.apply {

            paymentInfo = getSerializable("PaymentInfo") as PaymentInfo?

        }



        val calculateBox = findViewById<TextView>(R.id.perPersonBox)
        val tipAmountBox = findViewById<TextView>(R.id.tipAmountBox)
        val totalAmountBox = findViewById<TextView>(R.id.totalAmountBox)

        val amount = paymentInfo?.bilAmount
        val tip = paymentInfo?.tipPercentage
        val people = paymentInfo?.peopleAmount



        tipAmountBox.text = amount
        totalAmountBox.text = tip
        calculateBox.text = people
    }
}