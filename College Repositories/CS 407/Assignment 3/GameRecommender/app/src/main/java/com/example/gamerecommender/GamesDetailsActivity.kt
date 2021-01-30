package com.example.gamerecommender

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.ImageView
import android.widget.RatingBar
import android.widget.TextView
import com.bumptech.glide.Glide
import com.bumptech.glide.load.resource.bitmap.CenterCrop


const val MOVIE_BACKDROP = "extra_movie_backdrop"
const val MOVIE_TITLE = "extra_movie_title"
const val MOVIE_RATING = "extra_movie_rating"
const val MOVIE_RELEASE_DATE = "extra_movie_release_date"
const val GAME_RATINGS = "extra_game_ratings"
const val GAME_ADDED = "extra_added"
const val GAME_SUGGESTED = "extra_suggested"



class MovieDetailsActivity : AppCompatActivity() {
    private lateinit var backdrop: ImageView
    private lateinit var title: TextView
    private lateinit var rating: RatingBar
    private lateinit var releaseDate: TextView
    private lateinit var ratings: TextView
    private lateinit var added: TextView
    private lateinit var suggested: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_game_details)
        backdrop = findViewById(R.id.movie_backdrop)
        title = findViewById(R.id.movie_title)
        rating = findViewById(R.id.movie_rating)
        releaseDate = findViewById(R.id.movie_release_date)
        ratings = findViewById(R.id.game_ratings)
        added = findViewById(R.id.added_Value_Box)
        suggested = findViewById(R.id.suggested_Box_Value)



        val extras = intent.extras
        if (extras != null) {
            populateDetails(extras)
        } else {
            finish()
        }

    }




    private fun populateDetails(extras: Bundle) {
        extras.getString(MOVIE_BACKDROP)?.let { backdropPath ->
            Glide.with(this)
                .load("$backdropPath")
                .transform(CenterCrop())
                .into(backdrop)
        }

        title.text = extras.getString(MOVIE_TITLE, "")
        rating.rating = extras.getFloat(MOVIE_RATING, 0f)
        releaseDate.text =extras.getString(MOVIE_RELEASE_DATE, "")
        ratings.text = extras.getString(GAME_RATINGS, "")
        suggested.text = extras.getString(GAME_SUGGESTED, "0")
        added.text=extras.getString(GAME_ADDED, "0")

    }




}
