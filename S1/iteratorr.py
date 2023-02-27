


class Iterator:
    def __init__(self, bag):
        self.bag = bag
        self.iterator = 0
            #if len(bag) > 0 else None

    def valid(self):
        return self.iterator in range(len(self.bag))

    def first(self):
        if self.valid():
            return self.bag.item_list[0]
        else:
            return None

    def next(self):
        if self.valid():
            self.iterator += 1
            return self.bag[self.iterator]
        else:
            raise Exception("Error")

    def get_current(self):
        if self.valid():
            return self.bag[self.iterator]
        else:
            raise Exception