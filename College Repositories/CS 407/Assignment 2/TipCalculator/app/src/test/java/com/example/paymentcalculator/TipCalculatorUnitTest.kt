package com.example.paymentcalculator

import org.junit.Test

import org.junit.Assert.*

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * See [testing documentation](http://d.android.com/tools/testing).
 */
class TipCalculatorUnitTest {
    @Test
    fun calculateTipShouldEqual30() {
        val test = calculatePerPersonTotal((100.00).toFloat(), 4, 20)
        assertEquals((30.00).toFloat(), test, (0.01).toFloat())
    }

    @Test
    fun calculateTipShouldEqual100() {
        val test = calculatePerPersonTotal((100.00).toFloat(), 1, 0)
        assertEquals((100.00).toFloat(), test, (0.01).toFloat())
    }

    @Test
    fun calculateTipShouldEqual0() {
        val test = calculatePerPersonTotal((0.00).toFloat(), 20, 100)
        assertEquals((0.00).toFloat(), test, (0.01).toFloat())
    }

    @Test
    fun calculateTipShouldEqual3250() {
        val test = calculatePerPersonTotal((100.00).toFloat(), 4, 30)
        assertEquals((0.00).toFloat(), test, (32.50).toFloat())
    }

    @Test
    fun calculateTipShouldEqual3375() {
        val test = calculatePerPersonTotal((100.00).toFloat(), 4, 35)
        assertEquals((0.00).toFloat(), test, (33.75).toFloat())
    }

}
