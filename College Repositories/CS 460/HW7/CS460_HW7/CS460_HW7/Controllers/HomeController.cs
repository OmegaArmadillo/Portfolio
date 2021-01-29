using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Web;
using System.Web.Mvc;



namespace CS460_HW7.Controllers
{
    
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            //get the key
            string key = System.Configuration.ConfigurationManager.AppSettings["gitKey"];
            Debug.WriteLine(key);

            //get the user
            string user = "OmegaArmadillo";

            //get the user information
            string userData = SendRequest("https://api.github.com/user", key, user);
            JObject userObj = JObject.Parse(userData);

            //find the user information from the data
            ViewBag.Login = userObj["login"];
            ViewBag.ProfilePic = userObj["avatar_url"];
            ViewBag.Name = userObj["name"];
            ViewBag.Company = userObj["company"];
            ViewBag.Location = userObj["location"];
            ViewBag.EMail = userObj["email"];
            ViewBag.ProfileLink = userObj["html_url"];


           // Debug.WriteLine("https://api.github.com/user/" + user + "/repos");

            //get the repo data
            string repoData = SendRequest("https://api.github.com/user/repos", key, user);
            JArray repoObj = JArray.Parse(repoData);

            //make the lists to hold the repo ratio
            List<string> repoName = new List<string>();
            List<string> repoOwner = new List<string>();
            List<string> repoOwnerPic = new List<string>();
            List<string> repoLastUpdated = new List<string>();
            List<string> repoUrl = new List<string>();

            //add the data to the lists
            int count = repoObj.Count;
            for(int i = 0; i < count; i++)
            {
                repoName.Add((string)repoObj[i]["name"]);
                repoOwner.Add((string)repoObj[i]["owner"]["login"]);
                repoOwnerPic.Add((string)repoObj[i]["owner"]["avatar_url"]);
                repoLastUpdated.Add((string)repoObj[i]["updated_at"]);
                repoUrl.Add((string)repoObj[i]["html_url"]);
            }

            //set the viewbags
            ViewBag.repoName = repoName;
            ViewBag.repoOwner = repoOwner;
            ViewBag.repoOwnerPic = repoOwnerPic;
            ViewBag.repoLastUpdated = repoLastUpdated;
            ViewBag.repoUrl = repoUrl;
            ViewBag.count = count;

            return View();
        }


        public JsonResult getCommits(string user, string repo)
        {
            //get the data
            string commitUrl = "https://api.github.com/repos/" + user + "/" + repo + "/commits";
           // Debug.Write(commitUrl);
            string key = System.Configuration.ConfigurationManager.AppSettings["gitKey"];
            string userName = "OmegaArmadillo";

            string commitData = SendRequest(commitUrl, key, userName);
            JArray commitObj = JArray.Parse(commitData);

            //make the lists
            List<string> commitSha = new List<string>();
            List<string> commitAuthorName = new List<string>();
            List<string> commitDate = new List<string>();
            List<string> commitMessage = new List<string>();
            List<string> commitLink = new List<string>();

            //put the data into the lists
            int count = commitObj.Count;
            for (int i = 0; i < count; i++)
            {
                commitSha.Add((string)commitObj[i]["sha"]);
                commitAuthorName.Add((string)commitObj[i]["commit"]["author"]["name"]);
                commitDate.Add((string)commitObj[i]["commit"]["author"]["date"]);
                commitMessage.Add((string)commitObj[i]["commit"]["message"]);
                commitLink.Add((string)commitObj[i]["html_url"]);
            }

            //make the data that is sent to the javascript
            var commitSendData = new
            {
                sha = commitSha,
                name = commitAuthorName,
                date = commitDate,
                message = commitMessage,
                link = commitLink
            };

            //return the data
            return Json(commitSendData, JsonRequestBehavior.AllowGet);
        }

        private string SendRequest(string uri, string credentials, string username)
        {
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(uri);
            request.Headers.Add("Authorization", "token " + credentials);
            request.UserAgent = username;       // Required, see: https://developer.github.com/v3/#user-agent-required
            request.Accept = "application/json";

            string jsonString = null;
            // TODO: You should handle exceptions here
            using (WebResponse response = request.GetResponse())
            {
                Stream stream = response.GetResponseStream();
                StreamReader reader = new StreamReader(stream);
                jsonString = reader.ReadToEnd();
                reader.Close();
                stream.Close();
            }
            return jsonString;
        }


    }
}