using CS460_HW5.Models;
using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace CS460_HW5.DAL
{
    public class HomeworkContext: DbContext
    {
        public HomeworkContext() : base("name=HomeworkDB")
        {
            Database.SetInitializer<HomeworkContext>(null);

        }

        public virtual DbSet<Homework> Homework { get; set; }
    }
}