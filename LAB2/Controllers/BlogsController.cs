using Microsoft.AspNetCore.Mvc;
using BlogProject22.Data;
using BlogProject22.Models;
using Microsoft.AspNetCore.Identity;


namespace BlogProject22.Controllers
{
    public class BlogsController : Controller
    {
        private readonly BlogsDBContext _db;
       
        public BlogsController(BlogsDBContext db)
        {
            _db = db;
            
        }
        public IActionResult Index()
        {
            IEnumerable<Blogs> objBlogsList = _db.Blogs.ToList();
            return View(objBlogsList);
        }

        public IActionResult Create() {
            return View();
        }
        [HttpPost]
        [ValidateAntiForgeryToken]
        public IActionResult Create(Blogs obj)
        {
            var blog = _db.Blogs.SingleOrDefault(u => u.BlogID == obj.BlogID);
            if (blog != null)
            {
                ModelState.AddModelError("BlogID", "Blog with this id already exists!");
            }
            else
            {
                if (ModelState.IsValid)
                {
                    obj.CreatedUserID = User.Identity.Name;
                    obj.CreatedUserEmail = "Author Email";
                    _db.Blogs.Add(obj);
                    _db.SaveChanges();
                    TempData["success"] = "Blog was successfuly edited!";
                    return RedirectToAction("Index");
                }
            }
            //create a check whether the parameters are unique.
            return View(obj);
        }

        public IActionResult Edit(int? TableID)
        {
            if (TableID == null || TableID == 0) {
                return NotFound();
            }
            var blogFromDB = _db.Blogs.Find(TableID);
            if (blogFromDB == null) {
                return NotFound();
            
            }
            return View(blogFromDB);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public IActionResult Edit(Blogs obj)
        {  
                if (ModelState.IsValid)
                {
                obj.CreatedUserID = User.Identity.Name;
                _db.Blogs.Update(obj);
                    _db.SaveChanges();
                    TempData["success"] = "Blog was successfuly edited!";
                    return RedirectToAction("Index");
                }
            
            //create a check whether the parameters are unique.
            return View(obj);
        }

        public IActionResult Delete(int? TableID)
        {
            if (TableID == null || TableID == 0)
            {
                return NotFound();
            }
            var blogFromDB = _db.Blogs.Find(TableID);
            if (blogFromDB == null)
            {
                return NotFound();

            }
            return View(blogFromDB);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public IActionResult DeletePOST(int? TableID)
        {
            var obj = _db.Blogs.Find(TableID);
            if (obj == null) {
                return NotFound();
            }
            //create a check whether the parameters are unique.
            if (ModelState.IsValid)
            {
                _db.Blogs.Remove(obj);
                _db.SaveChanges();
                TempData["success"] = "Blog was successfuly deleted!";
                return RedirectToAction("Index");
            }
            return View(obj);
        }

        public IActionResult Display(int? TableID)
        {
            if (TableID == null || TableID == 0)
            {
                return NotFound();
            }
            var blogFromDB = _db.Blogs.Find(TableID);
            if (blogFromDB == null)
            {
                return NotFound();

            }
            return View(blogFromDB);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public IActionResult DisplayPost(int? TableID)
        {
            var obj = _db.Blogs.Find(TableID);
            if (obj == null)
            {
                return NotFound();
            }
           
            return View(obj);
        }
    }
}

