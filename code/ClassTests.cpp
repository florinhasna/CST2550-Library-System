#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "HelperFunctions.h"
#include "Book.h"
#include "Person.h"

TEST_CASE("Class construction", "[class created]")
{
    Person aPerson;
    aPerson.setName("Florin Hasna");
    aPerson.setAddress("35 Hendon Way, NW9 7JN");
    aPerson.setEmail("gh435@live.mdx.ac.uk");
    REQUIRE(aPerson.getName() == "Florin Hasna");
    REQUIRE(aPerson.getAddress() == "35 Hendon Way, NW9 7JN");
    REQUIRE(aPerson.getEmail() == "gh435@live.mdx.ac.uk");

    Librarian aLibrarian(1990, "Florin Hasna", "35 Hendon Way, NW9 7JN", "gh435@live.mdx.ac.uk", 100000);
    REQUIRE(aLibrarian.getStaffID() == 1990);
    REQUIRE(aLibrarian.getName() == "Florin Hasna");
    REQUIRE(aLibrarian.getAddress() == "35 Hendon Way, NW9 7JN");
    REQUIRE(aLibrarian.getEmail() == "gh435@live.mdx.ac.uk");
    REQUIRE(aLibrarian.getSalary() == 100000);

    Member aMember(1221, "Tikou Hyseni", "35 Hendon Way, NW9 7JN", "tikou@live.mdx.ac.uk");
    REQUIRE(aMember.getMemberId() == to_string(1221));
    REQUIRE(aMember.getName() == "Tikou Hyseni");
    REQUIRE(aMember.getAddress() == "35 Hendon Way, NW9 7JN");
    REQUIRE(aMember.getEmail() == "tikou@live.mdx.ac.uk");

    Member anotherMember(2112, "Gheorghe Hasna", "35 Hendon Way, NW9 7JN", "gheorghe@live.mdx.ac.uk");

    Book aBook(199, "The Hobbit", "John", "RR Tolkien");
    REQUIRE(aBook.getBookID() == "199");
    REQUIRE(aBook.getBookName() == "The Hobbit");
    REQUIRE(aBook.getAuthorFirstName() == "John");
    REQUIRE(aBook.getAuthorLastName() == "RR Tolkien");

    Book anotherBook(200, "The Lord of The Rings", "John", "RR Tolkien");

    Book* ptr;
    ptr = &aBook;
    aMember.setBooksBorrowed(ptr);
    ptr = nullptr;
    ptr = &anotherBook;
    aMember.setBooksBorrowed(ptr);
    REQUIRE((int) aMember.getBooksBorrowed().size() == 2);

    aMember.setBooksBorrowed(ptr); // as it is already borrowed by the member, the method will return the book
    REQUIRE((int) aMember.getBooksBorrowed().size() == 1);
    aMember.setBooksBorrowed(ptr); // check ability to issue it again
    REQUIRE((int) aMember.getBooksBorrowed().size() == 2);

    ptr = nullptr;
}