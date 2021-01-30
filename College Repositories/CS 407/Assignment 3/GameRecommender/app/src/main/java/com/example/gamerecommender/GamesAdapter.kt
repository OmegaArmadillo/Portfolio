package com.example.gamerecommender

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import androidx.recyclerview.widget.RecyclerView
import com.bumptech.glide.Glide
import com.bumptech.glide.load.resource.bitmap.CenterCrop


class GamesAdapter(
   // private var games: MutableList<Game>
    private var games: MutableList<Game>,
    private val onMovieClick: (game: Game) -> Unit
) : RecyclerView.Adapter<GamesAdapter.MovieViewHolder>()  {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): MovieViewHolder {
        val view = LayoutInflater
            .from(parent.context)
            .inflate(R.layout.item_game, parent, false)
        return MovieViewHolder(view)
    }

    override fun getItemCount(): Int = games.size

    override fun onBindViewHolder(holder: MovieViewHolder, position: Int) {
        holder.bind(games[position])
    }
    fun appendMovies(games: List<Game>) {
        this.games.addAll(games)
        notifyItemRangeInserted(
            this.games.size,
            games.size - 1
        )
    }



    inner class MovieViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {

        private val poster: ImageView = itemView.findViewById(R.id.item_movie_poster)

        fun bind(game: Game) {
            Glide.with(itemView)
                .load("${game.posterPath}")
                .transform(CenterCrop())
                .into(poster)
            itemView.setOnClickListener { onMovieClick.invoke(game)}
        }
    }
}