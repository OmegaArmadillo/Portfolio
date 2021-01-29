using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS460_HW3
{
    public class QueueUnderflowException : Exception
    {
        public QueueUnderflowException() : base()
        {
 
        }

        public QueueUnderflowException(String message) : base(message)
        {

        }

    }
}
