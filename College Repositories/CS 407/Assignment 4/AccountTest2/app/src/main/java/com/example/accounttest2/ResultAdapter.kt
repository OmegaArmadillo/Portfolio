package com.example.accounttest2



import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.BaseAdapter
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import androidx.recyclerview.widget.RecyclerView.ViewHolder


class ResultAdapter (private val context: Context, private val resultList: ArrayList<GameResult>) : BaseAdapter(){





    private val inflater: LayoutInflater
            = context.getSystemService(Context.LAYOUT_INFLATER_SERVICE) as LayoutInflater


    override fun getCount(): Int {
        return resultList.size
    }




    override fun getView(position: Int, convertView: View?, parent: ViewGroup?): View {
        val view: View
        val holder: ViewHolder

        // 1
        if (convertView == null) {

            // 2
            view = inflater.inflate(R.layout.list_item, parent, false)

            // 3
            holder = ViewHolder()
            holder.playerNameText = view.findViewById(R.id.playerNameText) as TextView
            holder.roundsCompletedText = view.findViewById(R.id.roundsCompletedText) as TextView
            holder.difficultyText = view.findViewById(R.id.difficultyText) as TextView


            // 4
            view.tag = holder
        } else {
            // 5
            view = convertView
            holder = convertView.tag as ViewHolder
        }

        // 6
        val playerNameText = holder.playerNameText
        val roundsCompletedText = holder.roundsCompletedText
        val difficultyText = holder.difficultyText

        val result = getItem(position) as GameResult

        playerNameText.text = result.player
        roundsCompletedText.text = result.rounds.toString()
        difficultyText.text = result.difficulty


        return view}

    override fun getItem(position: Int): Any {
        return resultList[position]
    }

    override fun getItemId(position: Int): Long {
        return position.toLong()
    }

    private class ViewHolder {
        lateinit var playerNameText: TextView
        lateinit var roundsCompletedText: TextView
        lateinit var difficultyText: TextView
    }


}



//
//
//import android.content.Context
//import android.view.LayoutInflater
//import android.view.View
//import android.view.ViewGroup
//import android.widget.BaseAdapter
//import android.widget.TextView
//import androidx.recyclerview.widget.RecyclerView
//
////import androidx.recyclerview.widget.RecyclerView
////import androidx.recyclerview.widget.RecyclerView.ViewHolder
//
//
//class ResultAdapter (private val resultList: ArrayList<GameResult>){
//
//    private var listener: View.OnClickListener? = null
//
//    fun setListener(clickListener: View.OnClickListener) {
//        this.listener = clickListener
//    }
//
//
//    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
//        val todo: GameResult = resultList[position]
//        holder.bindItems(todo)
//
//        holder.itemView.setOnClickListener(View.OnClickListener {
//            if (listener != null) {
//                listener!!.onItemClick(todo, position)
//            }
//        })
//
//        holder.itemView.btDelete.setOnClickListener(View.OnClickListener {
//            if (listener != null) {
//                listener!!.onItemDelete(todo)
//            }
//        })
//    }
//
//
//
//    override fun getItemCount(): Int {
//        return resultList.size
//    }
//
//
//    override fun onCreateViewHolder(parent: ViewGroup?, viewType: Int): ViewHolder {
//        return ViewHolder(LayoutInflater.from(parent!!.context).inflate(R.layout.list_item, parent, false))
//    }
//
//
//    class ViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
//        fun bindItems(result: GameResult) {
//            val playerNameText = itemView.findViewById<TextView>(R.id.playerNameText)
//            val roundsCompletedText = itemView.findViewById<TextView>(R.id.roundsCompletedText)
//            val difficultyText = itemView.findViewById<TextView>(R.id.difficultyText)
//            playerNameText.text = result.player
//            roundsCompletedText.text = result.rounds.toString()
//            difficultyText.text = result.difficulty
//        }
//    }
//
//
//
//
//
//    interface OnClickListener {
//        fun onItemClick(result: GameResult, position: Int)
//        fun onItemDelete(result: GameResult)
//    }
//
//
//}