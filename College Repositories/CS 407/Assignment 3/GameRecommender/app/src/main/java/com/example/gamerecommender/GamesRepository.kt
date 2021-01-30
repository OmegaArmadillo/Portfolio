package com.example.gamerecommender

import android.util.Log
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory

object GamesRepository {
    private val api : API

    init {
        val retrofit = Retrofit.Builder()
           // .baseUrl("https://api-v3.igdb.com")
            .baseUrl("https://api.rawg.io/api/")
            .addConverterFactory(GsonConverterFactory.create())
            .build()

        api = retrofit.create(API::class.java)
    }

    fun getPopularMovies (
        page : Int = 1,
        onSuccess : (games : List<Game>) -> Unit,
        onError : () -> Unit) {

        api.getPopularMovies(page = page)
            .enqueue(object : Callback<GetGamesResponse> {

                override fun onFailure(call: Call<GetGamesResponse>, t: Throwable) {
                    Log.d("RETROFIT: ", t.toString(), t)
                    onError.invoke()

                }

                override fun onResponse(
                    call: Call<GetGamesResponse>,
                    response: Response<GetGamesResponse>
                )
                {

                    val responseBody = response.body()
                    onSuccess.invoke(responseBody!!.games)
                    Log.d("Repository", "Movies: ${responseBody?.games}")
                }

            })
    }
}