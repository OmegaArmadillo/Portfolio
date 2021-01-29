using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Net;
using System.Web;
using System.Web.Mvc;
using System.Web.Script.Serialization;
using CS460_HW6.DAL;
using CS460_HW6.Models;
using CS460_HW6.Models.ViewModels;

namespace CS460_HW6.Controllers
{
    public class StockItemsController : Controller
    {
        private WWIContext db = new WWIContext();

        // GET: StockItems
        public ActionResult Index()
        {
            var stockItems = db.StockItems.Where(m => m.StockItemID == 0);
            //ViewBag.Search = "USB";
            //var stockItems = db.StockItems;
            return View(stockItems.ToList());
        }

        [HttpPost]
        public ActionResult Index(string searchInput)
        {
            var stockItems = db.StockItems.Where(m => m.StockItemName.Contains(searchInput));
            //ViewBag.Search = search;
            //var stockItems = db.StockItems;
            return View(stockItems.ToList());
        }


        // GET: StockItems/Details/5
        public ActionResult Details(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            StockItem stockItem = db.StockItems.Find(id);

    
            Person contact = db.People.Find(db.StockItems.Find(id).Supplier.PrimaryContactPersonID);

            

            decimal totalOrders = db.OrderLines.Where(m => m.StockItem.StockItemID == id).Select(t => t.Quantity).Count();
            decimal grossSales = db.InvoiceLines.Where(m => m.StockItem.StockItemID == id).Sum(t => t.ExtendedPrice);
            decimal grossProfit = db.InvoiceLines.Where(m => m.StockItem.StockItemID == id).Sum(t => t.LineProfit);


            var orderList = db.InvoiceLines.Where(t => t.StockItem.StockItemID == id).GroupBy(t => t.Invoice.Customer.CustomerName).Select(s => new { Buyer = s.Key, Amount = s.Sum(v => v.Quantity) }).OrderByDescending(x => x.Amount).Take(10).ToArray();
            //var orderList = db.InvoiceLines.Where(t => t.StockItem.StockItemID == 129).GroupBy(t => t.Invoice.Customer.CustomerName).Select(s => new { Buyer = s.Key, Amount = s.Sum(v => v.Quantity) }).OrderByDescending(x => x.Amount).Take(10);
            int length = orderList.Length;
            string[] buyerNames = new string[length];
            int[] buyerAmounts = new int[length];

            for(int i = 0; i < length; i++)
            {
                buyerNames[i] = orderList[i].Buyer;
                buyerAmounts[i] = orderList[i].Amount;
            }

            ProductDetails details = new ProductDetails(stockItem, contact, totalOrders, grossSales, grossProfit, buyerNames, buyerAmounts);

            if (stockItem == null)
            {
                return HttpNotFound();
            }
            return View(details);
        }
  


        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                db.Dispose();
            }
            base.Dispose(disposing);
        }
    }
}
