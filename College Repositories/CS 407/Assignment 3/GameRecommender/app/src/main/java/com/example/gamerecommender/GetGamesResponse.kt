package com.example.gamerecommender

import com.google.gson.annotations.SerializedName

data class GetGamesResponse (
    @SerializedName("page") val page : Int,
    @SerializedName("results") val games : List<Game>,
    @SerializedName("total_pages") val pages : Int
)