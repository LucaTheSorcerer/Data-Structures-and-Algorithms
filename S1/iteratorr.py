class Iterator:
    def __init__(self, bag):
        self.bag = bag
        self.iterator = 0


    def next(self):
        if self.valid():
            self.iterator += 1
            return self.iterator
        else:
            raise Exception("Not working properly")

    def first(self):
        if self.valid():
            return self.bag.item_list[0]
        else:
            return False
    def valid(self):
        return self.iterator in range(self.bag.size())

    def get_current(self):
        if self.valid():
            return self.bag[self.iterator]
        else:
            raise Exception("Not working properly!")