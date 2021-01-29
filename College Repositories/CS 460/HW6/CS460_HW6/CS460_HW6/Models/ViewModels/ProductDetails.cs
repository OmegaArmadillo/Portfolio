using Microsoft.Ajax.Utilities;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Web.Script.Serialization;

namespace CS460_HW6.Models.ViewModels
{
    public class ProductDetails
    {
      

        public ProductDetails(StockItem product,Person contact, decimal totalOrders, decimal grossSales, decimal grossProfit, string[] buyerName, int[] buyerAmount)
         {
            StockItemName = product.StockItemName;
            Size = product.Size;
            RecommendedRetailPrice = product.RecommendedRetailPrice;
            TypicalWeightPerUnit = product.TypicalWeightPerUnit;
            LeadTimeDays = product.LeadTimeDays;

            
            ValidFrom = product.ValidFrom.Date.ToString();


            //https://stackoverflow.com/questions/12676746/parse-json-string-in-c-sharp
            dynamic customFields = Newtonsoft.Json.JsonConvert.DeserializeObject(product.CustomFields);
            string origin = customFields.CountryOfManufacture;

            CustomFields = origin;

            //https://stackoverflow.com/questions/7411438/remove-characters-from-c-sharp-string
              string tags = String.Join("", product.Tags.Split('[', ']', '{', '}','"'));
            Tags = tags;

            Photo = product.Photo;
            
            SupplierName = product.Supplier.SupplierName;
            SupplierPhoneNumber = product.Supplier.PhoneNumber;
            SupplierFaxNumber = product.Supplier.FaxNumber;
            SupplierWebsiteURL = product.Supplier.WebsiteURL;
            SupplierContactFullName = contact.FullName;

            TotalOrders = Decimal.ToInt32(totalOrders);
            GrossSales = grossSales;
            GrossProfit = grossProfit;

            BuyerNames = buyerName;
            BuyerAmount = buyerAmount;





         }


        public string StockItemName { get; set; }

        [StringLength(20)]
        public string Size { get; set; }

        public decimal? RecommendedRetailPrice { get; set; }

        public decimal TypicalWeightPerUnit { get; set; }

        public int LeadTimeDays { get; set; }

        
        public String ValidFrom { get; set; }

        public string CustomFields { get; set; }

        [DatabaseGenerated(DatabaseGeneratedOption.Computed)]
        public string Tags { get; set; }

        public byte[] Photo { get; set; }


        //Supplier Section

        [StringLength(100)]
        public string SupplierName { get; set; }

        [StringLength(20)]
        public string SupplierPhoneNumber { get; set; }

        [StringLength(20)]
        public string SupplierFaxNumber { get; set; }

        [StringLength(256)]
        public string SupplierWebsiteURL { get; set; }

        [StringLength(50)]
        public string SupplierContactFullName { get; set; }

        public int TotalOrders { get; set; }

        public decimal GrossSales { get; set; }

        public decimal GrossProfit { get; set; }

        public string[] BuyerNames { get; set; }

        public int[] BuyerAmount { get; set; }
    }
}