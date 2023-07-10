using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
using BlogProject22.Areas.Identity.Pages.Account.Manage;
using Microsoft.AspNetCore.Identity;
using BlogProject22.Models;

namespace BlogProject22.Models
{
    public class Blogs
    {
        public string CreatedUserID { set; get; } = "Some guy";
        public string CreatedUserEmail { set; get; } = "Some guy";
        [Key]
        public int TableID { set; get; }
        //[Required(ErrorMessage = "Blog ID is required!")]
        [Required(ErrorMessage = "Blog ID is required! It should be of the integer type")]
        public int BlogID { set; get; }
        [Required(ErrorMessage = "Blog Title is required!")]
        public string BlogTitle { set; get; }
        [Required(ErrorMessage = "Blog content is required!")]
        public string BlogContent { set; get; }
        public DateTime TimeOfCreation { get; set; } = DateTime.Now;
       
    }
}
