# c-data-structures-api-for-php

So far PHP only supports hash table (aka "array") as native data structure. This means whenever one needs a different data structure (eg: list) the only way to do it is via "array" (eg: operator[] for lists), which creates massive performance costs (high CPU time as well as memory consumption). This extension is aimed at fixing this problem by:

* adding native C/C++ implementations for missing data structures that will become available to all PHP programmers using this extension
* adding features missing in default hash table implementation (eg: using objects as keys)
* adding type-aware support (eg: list with SPECIFICALLY integer values) to all data structures implemented which brings huge performance benefits whenever they map to native C/C++ types

Development will be done in steps. Each step is complete only after thorough unit-testing. The list of steps are:

1. Implementation of Lists. COMPLETE!!!
2. Implementation of Maps
3. Implementation of Sets
4. Implementation of Stacks & Queues
5. Implementation of Trees

<strong>So far the extension is already tested and usable if you want to use Lists only.</strong> 

<h2>LISTS</h2>
Exposed PHP classes are:

- <strong>ArrayList</strong>: a list implemented using <a href="https://en.wikipedia.org/wiki/Dynamic_array">dynamic arrays</a>, 
	good for:
		- fastest insertion on bottom
		- fastest deletion from bottom
		- fastest random access of elements
		- smallest memory consumption
	very bad for:
		- insertion on top
		- deletion from any position other than bottom
- <strong>LinkedList</strong>: a list implemented using <a href="https://en.wikipedia.org/wiki/Linked_list">linked lists</a>, 
	good for:
		- fast insertion on top/bottom
		- fast deletion of next elements (compared to head or iterator* position)
		- fast access of next element (compared to head or iterator* position)
	bad for:
		- random access of elements
		- deletion of any element other than next (compared to head or iterator* position)
		- larger memory consumption
- <strong>DoublyLinkedList</strong>: a list implemented using <a href="https://en.wikipedia.org/wiki/Doubly_linked_list">doubly linked lists</a>, 
	good for:
		- fast insertion on top/bottom
		- fast deletion of next/previous elements (compared to head, tail or iterator* position)
		- fast access of next/previous element (compared to head, tail or iterator* position)
	bad for:
		- random access of elements
		- deletion of any element other than next/previous (compared to head, tail or iterator* position)
		- largest memory consumption
<small>* To speed up operations, both linked lists and doubly linked list use an internal iterator that points to current node as you traverse list's contents. Any operation that involves an element (get/set/delete) modifies iterator as well.</small>

All three classes implement <strong>Lists</strong> interface, which defines following operations:
<table>
	<thead>
		<tr>
			<td>Method</td>
			<td>Description</td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>addToTop (TYPE $value)</td>
			<td>Adds value to top of list.</td>
		</tr>
		<tr>
			<td>addToBottom (TYPE $value)</td>
			<td>Adds value to bottom of list.</td>
		</tr>
		<tr>
			<td>set (int $position, TYPE $value)</td>
			<td>Sets value by position</td>
		</tr>
		<tr>
			<td>emplace (int $position, TYPE $value)</td>
			<td>Inserts value by position, padding existing one to the right</td>
		</tr>
		<tr>
			<td>get (int $position)</td>
			<td>Gets value by position.</td>
		</tr>
		<tr>
			<td>containsIndex (int $position)</td>
			<td>Checks if list contains position.</td>
		</tr>
		<tr>
			<td>containsValue (TYPE $value)</td>
			<td>Checks if list contains value.</td>
		</tr>
		<tr>
			<td>removeIndex (int $position)</td>
			<td>Removes value from list by position.</td>
		</tr>
		<tr>
			<td>removeValue (TYPE $value)</td>
			<td>Removes value from list by value.</td>
		</tr>
		<tr>
			<td>isEmpty ()</td>
			<td>Checks if list is empty.</td>
		</tr>
		<tr>
			<td>size ()</td>
			<td>Gets list size (number of elements).</td>
		</tr>
		<tr>
			<td>clear ()</td>
			<td>Empties list.</td>
		</tr>
	</tbody>
</table>
where TYPE can be any valid <a href="http://php.net/manual/ro/language.types.php">PHP type</a>.
	
Because PHP so far doesn't support <a href="https://en.wikipedia.org/wiki/Generic_programming">generics</a>, in order for lists to be type-aware, constructors for classes that implement Lists (ArrayList, LinkedList, DoublyLinkedList) have a single non-optional argument that identifies type of values inside. Types can be:
1. "mixed": this means list will store values of ANY type. Slower and more memory-hungry by orders of magnitude compared to below. Rarely if ever needed in real-life experience.
2. "int"/"integer": this means list is optimized to only hold values of C long type. Extremely fast and with lowest memory consumption.
3. "double"/"float": this means list is optimized to only hold values of C double type. Extremely fast and with lowest memory consumption.
4. "string": this means list is optimized to only hold values of C char* type. Very fast and with low memory consumption.
5. your-class/interface-name: this means list will only hold objects of your desired class/interface. Slightly slower than 1# because it type-validates every entry with instanceof and just as memory-hungry (both holding values of C <a href="http://php.net/manual/en/internals2.variables.intro.php">zval*</a> type).
Of course, all slowness and memory-hungriness mentioned above are relative. When compared to standard PHP array, any list, regardless of implementation or value type, is MUCH more optimal (as benchmarks below show).


Example: 
$list = new ArrayList("string"); // if php would supported generics, it would have been ArrayList<string>