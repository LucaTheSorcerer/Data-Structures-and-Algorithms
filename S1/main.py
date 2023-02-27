from bagg import Bagg
from iteratorr import Iterator
def main():
    bag = Bagg()

    bag.add(100)
    bag.add(100)
    bag.add(250)
    bag.add(6)
    bag.add(15)

    print(bag.size())

    assert bag.nr_occurrences(100)

    try:
        assert bag.size() == 5
    except AssertionError:
        print("Size is bigger or lower than the actual size of the bag")

    assert bag.search(6)

    bag.add(500)
    assert bag.search(500)
    bag.remove(500)

    try:
        assert  bag.search(500)
    except AssertionError:
        print("Not valid")

    iter = bag.iterator()

    try:
        assert type(iter) == Iterator
    except AssertionError:
        print("Iterators are not the same")

    try:
        assert iter.first() == bag.item_list[0]
    except AssertionError:
        print("Invalid")

    iter.next()
    assert iter.iterator == 1


    try:
        iter.next()
        assert True
    except:
        bag.destroy()

    bag.destroy()

main()
