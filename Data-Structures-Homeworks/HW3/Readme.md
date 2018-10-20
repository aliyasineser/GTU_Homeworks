SpecList;
- must extend JAVA-LinkedList
- has three extra procedures that perform the following tasks

  1. Appends all of the elements in the specified collection to the head of the list.
  
  Boolean addAllAtHead(Collection<? extends E> c)
  
  2. Finds and returns intersection list (list of unique elements available in both collections)
  
  List<E> getIntersectList (Collection<? extends E> c)
  
  3. Sorts and returns list (use cocktail sort algorithm)
  
  List<E> sortList(decreasing_or_increasing)
