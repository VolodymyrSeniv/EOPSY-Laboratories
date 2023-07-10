
using Microsoft.EntityFrameworkCore;
using BlogProject22.Models;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;

namespace BlogProject22.Data
{
    public class BlogsDBContext : IdentityDbContext
    {
        public BlogsDBContext(DbContextOptions<BlogsDBContext> options) :base(options)
        {

        }

        public DbSet<Blogs> Blogs { get; set; }
        public DbSet<UserAccounts> UserAccount { get; set; }
    }
}
