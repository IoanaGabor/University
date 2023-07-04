class ConsoleUI:

    def __init__(self, service):
        self.__service = service

    @staticmethod
    def __print_menu():
        print("Options:\n"
              "1. Add a book.\n"
              "2. Display all books\n"
              "3. Filter out books with a certain starting word\n"
              "4. Undo the last operation\n"
              "0. Exit\n")

    def __add_book(self):
        isbn = input("Isbn: \n")
        author = input("Author: \n")
        title = input("Title: \n")
        try:
            self.__service.add_book(isbn, author, title)
        except ValueError as ve:
            print(ve)

    def __display_all(self):
        all_books = self.__service.list_all_books()
        for book in all_books:
            print(book)

    def __filter_out(self):
        starting_word = input("Enter the starting word:\n")
        try:
            self.__service.filter_out(starting_word)
        except Exception as ex:
            print(ex)

    def __undo(self):
        try:
            self.__service.undo()
        except Exception as ex:
            print(ex)

    def run(self):
        commands = {
            '1': self.__add_book,
            '2': self.__display_all,
            '3': self.__filter_out,
            '4': self.__undo,
        }
        while True:
            self.__print_menu()
            cmd = input("Please enter an option:\n")
            if cmd == "0":
                break
            if cmd not in commands.keys():
                print("Invalid command!")
            else:
                commands[cmd]()
