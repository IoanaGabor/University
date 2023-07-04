import json


class Book:
    def __init__(self, isbn, author, title):
        self.__isbn = isbn
        self.__author = author
        self.__title = title

    @property
    def isbn(self):
        return self.__isbn

    @property
    def author(self):
        return self.__author

    @author.setter
    def author(self, value):
        self.__author = value

    @property
    def title(self):
        return self.__title

    @title.setter
    def title(self, value):
        self.__title = value

    def __str__(self):
        return "The book with isbn {0} has the author {1} and the title {2}".format(self.__isbn, self.__author,
                                                                                    self.__title)

    def __eq__(self, other):
        return self.__isbn == other.__isbn and self.__title == other.__title and self.__author == other.__author

    @classmethod
    def from_text_line_to_book(cls, text_line):
        fields = text_line.split(",")
        if len(fields) != 3:
            raise Exception("Invalid text line found!")
        isbn = fields[0].strip()
        author = fields[1].strip()
        title = fields[2].strip()
        return cls(isbn, author, title)

    def from_book_to_text_line(self):
        return self.__isbn + "," + self.__author + ", " + self.__title


class BookEncoder(json.JSONEncoder):
    def default(self, o):
        if isinstance(o, Book):
            return {
                "isbn": o.isbn,
                "author": o.author,
                "title": o.title
            }
        else:
            return super().default(o)


class BookDecoder(json.JSONDecoder):
    def __init__(self, object_hook=None, *args, **kwargs):
        super().__init__(object_hook=self.object_hook, *args, **kwargs)

    @staticmethod
    def object_hook(o):
        decoded_book = Book(
            o.get('isbn'),
            o.get('author'),
            o.get('title'),
        )
        return decoded_book
