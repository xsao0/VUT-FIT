using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace xDrive.DAL.Migrations
{
    public partial class UpdateCarsFK : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Cars_Users_UserEntityId",
                table: "Cars");

            migrationBuilder.RenameColumn(
                name: "UserEntityId",
                table: "Cars",
                newName: "OwnerId");

            migrationBuilder.RenameIndex(
                name: "IX_Cars_UserEntityId",
                table: "Cars",
                newName: "IX_Cars_OwnerId");

            migrationBuilder.AddColumn<Guid>(
                name: "UserId",
                table: "Cars",
                type: "uniqueidentifier",
                nullable: false,
                defaultValue: new Guid("00000000-0000-0000-0000-000000000000"));

            migrationBuilder.AddForeignKey(
                name: "FK_Cars_Users_OwnerId",
                table: "Cars",
                column: "OwnerId",
                principalTable: "Users",
                principalColumn: "Id");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Cars_Users_OwnerId",
                table: "Cars");

            migrationBuilder.DropColumn(
                name: "UserId",
                table: "Cars");

            migrationBuilder.RenameColumn(
                name: "OwnerId",
                table: "Cars",
                newName: "UserEntityId");

            migrationBuilder.RenameIndex(
                name: "IX_Cars_OwnerId",
                table: "Cars",
                newName: "IX_Cars_UserEntityId");

            migrationBuilder.AddForeignKey(
                name: "FK_Cars_Users_UserEntityId",
                table: "Cars",
                column: "UserEntityId",
                principalTable: "Users",
                principalColumn: "Id");
        }
    }
}
