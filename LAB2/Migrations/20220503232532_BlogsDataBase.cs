using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace BlogProject22.Migrations
{
    public partial class BlogsDataBase : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Blogs",
                columns: table => new
                {
                    TableID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    CreatedUserID = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    CreatedUserEmail = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    BlogID = table.Column<int>(type: "int", nullable: false),
                    BlogTitle = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    BlogContent = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    TimeOfCreation = table.Column<DateTime>(type: "datetime2", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Blogs", x => x.TableID);
                });
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Blogs");
        }
    }
}
