from iteratorr import Iterator

class Bagg:
    def __init__(self):
        self.item_list = []

    def add(self, element):
        self.item_list.append(element)

    def remove(self, element):
        if self.search(element):
            self.item_list.remove(element)

        return self.search(element)

    def search(self, element):
        if element not in self.item_list:
            return False
        return element in self.item_list


    def size(self):
        return len(self.item_list)

    def nr_occurrences(self, element):
        return self.item_list.count(element)

    def iterator(self):
        return Iterator(self)

    """
    The destroy or destructor method is already implemented in Python by default because
    Python has garbage collection, unlike other languages 
    but below is a way of hard coding one using the del method
    """
    def destroy(self):
        del self.item_list