package com.example.paymentcalculator

import androidx.test.espresso.Espresso
import androidx.test.espresso.Espresso.onData
import androidx.test.espresso.Espresso.onView
import androidx.test.espresso.action.ViewActions
import androidx.test.espresso.action.ViewActions.click
import androidx.test.espresso.matcher.ViewMatchers
import androidx.test.espresso.matcher.ViewMatchers.withId
import androidx.test.platform.app.InstrumentationRegistry
import androidx.test.ext.junit.runners.AndroidJUnit4
import androidx.test.filters.LargeTest
import androidx.test.rule.ActivityTestRule

import org.junit.Test
import org.junit.runner.RunWith

import org.junit.Assert.*
import org.junit.Rule
import androidx.test.espresso.assertion.ViewAssertions
import org.hamcrest.CoreMatchers.*


/**
 * Instrumented test, which will execute on an Android device.
 *
 * See [testing documentation](http://d.android.com/tools/testing).
 */
@RunWith(AndroidJUnit4::class)
@LargeTest
class TipCalculatorInstrumentedTest {

    @get:Rule
    var activityRule: ActivityTestRule<MainActivity>
            = ActivityTestRule(MainActivity::class.java)


    fun useAppContext() {
        // Context of the app under test.
        val appContext = InstrumentationRegistry.getInstrumentation().targetContext
        assertEquals("com.example.paymentcalculator", appContext.packageName)
    }

    @Test
    fun textTest10() {

        Espresso.onView(ViewMatchers.withId(R.id.totalBox))
    .perform(ViewActions.typeText("100.00"), ViewActions.closeSoftKeyboard())

        Espresso.onView(ViewMatchers.withId(R.id.firstDigitSpinner))
            .perform(ViewActions.scrollTo())
            .perform(ViewActions.click());

        onData(allOf(`is`(instanceOf(String::class.java)))).atPosition(0).perform(click())


        Espresso.onView(ViewMatchers.withId(R.id.secondDigitSpinner))
            .perform(ViewActions.scrollTo())
            .perform(ViewActions.click());

        onData(allOf(`is`(instanceOf(String::class.java)))).atPosition(0).perform(click())


        Espresso.onView(ViewMatchers.withId(R.id.peopleBar))
            .perform(ViewActions.click())

        onView(withId(R.id.calculateButton)).perform(click())

        onView(withId(R.id.perPersonBox))
            .check(ViewAssertions.matches(ViewMatchers.withText("10.00")))
    }

    @Test
    fun textTest18() {

        Espresso.onView(ViewMatchers.withId(R.id.totalBox))
            .perform(ViewActions.typeText("120.00"), ViewActions.closeSoftKeyboard())

        Espresso.onView(ViewMatchers.withId(R.id.firstDigitSpinner))
            .perform(ViewActions.scrollTo())
            .perform(ViewActions.click());

        onData(allOf(`is`(instanceOf(String::class.java)))).atPosition(5).perform(click())


        Espresso.onView(ViewMatchers.withId(R.id.secondDigitSpinner))
            .perform(ViewActions.scrollTo())
            .perform(ViewActions.click());

        onData(allOf(`is`(instanceOf(String::class.java)))).atPosition(0).perform(click())


        Espresso.onView(ViewMatchers.withId(R.id.peopleBar))
            .perform(ViewActions.click())

        onView(withId(R.id.calculateButton)).perform(click())

        onView(withId(R.id.perPersonBox))
            .check(ViewAssertions.matches(ViewMatchers.withText("18.00")))
    }

    @Test
    fun textTest0() {

        Espresso.onView(ViewMatchers.withId(R.id.totalBox))
            .perform(ViewActions.typeText("0"), ViewActions.closeSoftKeyboard())

        Espresso.onView(ViewMatchers.withId(R.id.firstDigitSpinner))
            .perform(ViewActions.scrollTo())
            .perform(ViewActions.click());

        onData(allOf(`is`(instanceOf(String::class.java)))).atPosition(0).perform(click())


        Espresso.onView(ViewMatchers.withId(R.id.secondDigitSpinner))
            .perform(ViewActions.scrollTo())
            .perform(ViewActions.click());

        onData(allOf(`is`(instanceOf(String::class.java)))).atPosition(0).perform(click())


        Espresso.onView(ViewMatchers.withId(R.id.peopleBar))
            .perform(ViewActions.click())

        onView(withId(R.id.calculateButton)).perform(click())

        onView(withId(R.id.perPersonBox))
            .check(ViewAssertions.matches(ViewMatchers.withText("0.00")))
    }

    @Test
    fun textTestTotalError() {



        Espresso.onView(ViewMatchers.withId(R.id.firstDigitSpinner))
            .perform(ViewActions.scrollTo())
            .perform(ViewActions.click());

        onData(allOf(`is`(instanceOf(String::class.java)))).atPosition(0).perform(click())


        Espresso.onView(ViewMatchers.withId(R.id.secondDigitSpinner))
            .perform(ViewActions.scrollTo())
            .perform(ViewActions.click());

        onData(allOf(`is`(instanceOf(String::class.java)))).atPosition(0).perform(click())


        Espresso.onView(ViewMatchers.withId(R.id.peopleBar))
            .perform(ViewActions.click())

        onView(withId(R.id.calculateButton)).perform(click())

        onView(withId(R.id.errorBox))
            .check(ViewAssertions.matches(ViewMatchers.withText("You must have a value for total.")))
    }

    @Test
    fun textTestPeopleError() {

        Espresso.onView(ViewMatchers.withId(R.id.totalBox))
            .perform(ViewActions.typeText("0"), ViewActions.closeSoftKeyboard())

        Espresso.onView(ViewMatchers.withId(R.id.firstDigitSpinner))
            .perform(ViewActions.scrollTo())
            .perform(ViewActions.click());

        onData(allOf(`is`(instanceOf(String::class.java)))).atPosition(0).perform(click())


        Espresso.onView(ViewMatchers.withId(R.id.secondDigitSpinner))
            .perform(ViewActions.scrollTo())
            .perform(ViewActions.click());

        onData(allOf(`is`(instanceOf(String::class.java)))).atPosition(0).perform(click())


        onView(withId(R.id.calculateButton)).perform(click())

        onView(withId(R.id.errorBox))
            .check(ViewAssertions.matches(ViewMatchers.withText("You must have a value for people.")))
    }
}
