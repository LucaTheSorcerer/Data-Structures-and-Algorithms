
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
        if element in self.item_list:
            return element in self.item_list
        return False

    def size(self):
        return len(self.item_list)

    def nr_occurrences(self, element):
        return self.item_list.count(element)

    def destroy(self):
        del self.item_list



