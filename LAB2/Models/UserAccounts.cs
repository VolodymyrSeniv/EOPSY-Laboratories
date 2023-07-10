using Microsoft.AspNetCore.Identity;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;



namespace BlogProject22.Models
{
    public class UserAccounts : IdentityUser
    {
        [Required(ErrorMessage = "User ID is required! It should be of the integer type")]
        public int UserID { get; set; }

    }
}
