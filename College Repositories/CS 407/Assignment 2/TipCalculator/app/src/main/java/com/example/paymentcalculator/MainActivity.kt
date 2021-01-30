package com.example.paymentcalculator

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.*
import java.io.Serializable


class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)



        val totalBox = findViewById<EditText>(R.id.totalBox)
        val button = findViewById<Button>(R.id.calculateButton)
        val errorBox = findViewById<TextView>(R.id.errorBox)

       /*
        val calculateBox = findViewById<TextView>(R.id.perPersonBox)
        val tipAmountBox = findViewById<TextView>(R.id.tipAmountBox)
        val totalAmountBox = findViewById<TextView>(R.id.totalAmountBox)

        */


        val peopleBar = findViewById<SeekBar>(R.id.peopleBar)
        val peopleSelected = peopleBar.progress
        val progressBox = findViewById<TextView>(R.id.progressBox)
        progressBox.setText(getString(R.string.peopleHint)+ ": " + peopleSelected)


        val firstDigitSpinner = findViewById<Spinner>(R.id.firstDigitSpinner)
        val secondDigitSpinner = findViewById<Spinner>(R.id.secondDigitSpinner)
        val digits = resources.getStringArray(R.array.digits)

        val adapterFirst = ArrayAdapter(this, android.R.layout.simple_spinner_item, digits)
        val adapterSecond = ArrayAdapter(this, android.R.layout.simple_spinner_item, digits)

        var digitOne = "0"
        var digitTwo = "0"

        firstDigitSpinner.onItemSelectedListener = object : AdapterView.OnItemSelectedListener {
            override fun onNothingSelected(p0: AdapterView<*>?) {
                TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
            }

            override fun onItemSelected(p0: AdapterView<*>?, p1: View?, position: Int, p3: Long) {
                digitOne = digits[position]
            }

        }

        secondDigitSpinner.onItemSelectedListener = object : AdapterView.OnItemSelectedListener {
            override fun onNothingSelected(p0: AdapterView<*>?) {
                TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
            }

            override fun onItemSelected(p0: AdapterView<*>?, p1: View?, position: Int, p3: Long) {
                digitTwo = digits[position]
            }

        }

        firstDigitSpinner.adapter = adapterFirst
        secondDigitSpinner.adapter = adapterSecond



        val seekBarChangeListener = object : SeekBar.OnSeekBarChangeListener {

            override fun onProgressChanged(seekBar: SeekBar, progress: Int, fromUser: Boolean) {
                // updated continuously as the user slides the thumb
                progressBox.setText(getString(R.string.peopleHint)+ ": " + "$progress")
            }

            override fun onStartTrackingTouch(seekBar: SeekBar) {
                // called when the user first touches the SeekBar
            }

            override fun onStopTrackingTouch(seekBar: SeekBar) {
                // called after the user finishes moving the SeekBar
            }
        }

        peopleBar.setOnSeekBarChangeListener(seekBarChangeListener);



        button.setOnClickListener(View.OnClickListener {



            if(totalBox.text.toString().isEmpty())
            {
                errorBox.text=getString(R.string.amountErrorText)

            }
            else
            {

                    if(peopleBar.progress == 0)
                    {
                        errorBox.text=getString(R.string.peopleErrorText)

                    }
                    else
                    {


                        val amount = totalBox.text.toString().toFloat()
                        val tip = ((digitOne.toInt() * 10) + digitTwo.toInt())
                        val people = peopleBar.progress


                        val tipNumber = "%.2f".format( amount * (tip/100.00) )
                        val tipAndTotal =  "%.2f".format( amount + tipNumber.toFloat() )
                        val totalPerPerson = "%.2f".format(tipAndTotal.toFloat()/people.toFloat())


                        /*
                        tipAmountBox.text = tipNumber
                        totalAmountBox.text = tipAndTotal
                        calculateBox.text = totalPerPerson

                         */



                        val paymentInfo : PaymentInfo = PaymentInfo(tipNumber, tipAndTotal, totalPerPerson)

                        val intent : Intent = Intent(this, CalculationActivity::class.java)

                        intent.putExtra("PaymentInfo", paymentInfo as Serializable)

                        startActivity(intent)
                    }


            }




        })

    }






}
