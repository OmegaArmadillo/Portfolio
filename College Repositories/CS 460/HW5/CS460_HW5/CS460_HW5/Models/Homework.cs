using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace CS460_HW5.Models
{
    public class Homework
    {
        [Key]
        public int ID { get; set; }

        [Required, DisplayName("Homework Title")]
        [StringLength(100)]
        public string HomeworkTitle { get; set; }

        [Required]
        [StringLength(10)]
        public string Importance { get; set; }

        [Required, DisplayName("Due Date")]
        [StringLength(12)]
        public string DueDate { get; set; }

        [Required, DisplayName("Due Time")]
        [StringLength(12)]
        public string DueTime { get; set; }

        [Required]
        [StringLength(6)]
        public string Department { get; set; }

        [Required, DisplayName("Course #")]
        public int CourseNumber { get; set; }

        
        [StringLength(1000)]
        [DataType(DataType.MultilineText)]
        public string Notes { get; set; }

        [DisplayName("Full Due Date")]
        public DateTime FullDueDate
        {
            get
            {
                DateTime Date;
                try
                {
                    string full = DueDate + " " + DueTime;
                    Date = DateTime.Parse(full);
                }
                catch
                {
                   Date =new DateTime(2000,1,1,12,0,0);
                }
                
                return Date;
                
            }
        }
    }
}