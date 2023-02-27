from bagg import Bagg
from iteratorr import Iterator



def main():
    bag = Bagg()

    bag.add(100)
    bag.add(100)
    bag.add(250)
    bag.add(6)

    assert bag.nr_occurrences(100)

    assert bag.size() == 4


    assert bag.search(6)

    bag.remove(2)
    assert not bag.search(2)

    iterator = bag.iterator()

    assert type(iterator) == Iterator
    assert iterator.bag == bag
    assert iterator.first() == bag.lst[0]
    iterator.next()
    assert iterator.i == 1
    iterator.next()
    iterator.next()

    try:
        iterator.next()
        iterator.next()
        iterator.next()
        assert False
    except:
        bag.destroy()

        try:
            bag.lst

        except:
            # The delete method is implemented by pythons garbage collector by default
            del bag

            try:
                bag
            except NameError:
                pass


main()
