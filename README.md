# Advanced Binary Search

What if we wanted something _like_ Binary Search but with minor differences.
That is, instead of searching for an _exact_ match we wanted to find keys
that are "close" -- where close can mean one of 8 things:

* `LTS`:  Find the "sticky" item Less Then the Key or Size-1 if not found
* `LT`:   Find the first item Less Then the key, or -1 if not found
* `LTE`:  Find the first item Less Then Or Equal to the key, or -1 if not found
* `LTEN`: Find the next item Less Then or Equal to the Key or Size if not found
* `GTE`:  Find the first item Greater Than or Equal to the key
* `GT`:   Find the first item Greater Than the key
* 'GTS`:  Find the "sticky" item Greater Then the Key or 0 if not found

Note: The _ninth_ one `EQ` is the classic Binary Search. 

For example, given the array:

```Javascript
    [ 1, 3, 5, 7, 9, 11 ]
```

We could enumerate the various search results:

|Key| <S | <  | <= | <=S| == | >=N| >= |  > | >S |
|:--|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| -1|   0|   0|   0|   0| n/a|   0| n/a| n/a|   0|
|  0|   0|   0|   0|   0| n/a|   0| n/a| n/a|   0|
|  1|   1|   1|   0|   0|   0|   0|   0| n/a|   0|
|  2|   1|   1|   1|   1| n/a|   0|   0|   0|   0|
|  3|   2|   2|   1|   1|   1|   1|   1|   0|   0|
|  4|   2|   2|   2|   2| n/a|   1|   1|   1|   1|
|  5|   3|   3|   2|   2|   2|   2|   2|   1|   1|
|  6|   3|   3|   3|   3| n/a|   2|   2|   2|   2|
|  7|   4|   4|   3|   3|   3|   3|   3|   2|   2|
|  8|   4|   4|   4|   4| n/a|   3|   3|   3|   3|
|  9|   5|   5|   4|   4|   4|   4|   4|   3|   3|
| 10|   5|   5|   5|   5| n/a|   4|   4|   4|   4|
| 11|   5| n/a|   5|   5|   5|   5|   5|   4|   4|
| 12|   5| n/a| n/a|   5| n/a|   5| n/a|   5|   5|
| --| LTS|  LT| LTE|LTEN|  EQ|GTEN| GTE|  GT| GTS|

```
Legend:

  <S  Advanced Binary Search: pos where key <  data[pos], or size if not found
  <   Advanced Binary Search: pos where key <  data[pos]
  <=  Advanced Binary Search: pos where key <= data[pos]
 <=N  Advanced Binary Search: pos where key <= data[pos], or size-1 if not found
  ==  Exact    Binary Search: pos where key == data[pos], else -1
 >=N  Advanced Binary Search:
  >=  Advanced Binary Search: pos where key >= data[pos]
  >   Advanced Binary Search: pos where key >  data[pos]
  >S  Advanced Binary Search: pos where key >  data[pos], or size if not found
```

How do we find these algorithms?

Instead of returning when we find a key, lets output the current state:

```Javascript
    // ==================================================
    function BinSearchPrint( key, data )
    {
        var num = data.length - 1;
        var min = 0;
        var max = num;

        while( min <= max )
        {
            var mid = min + ((max - min) / 2) | 0;

            /**/ if (data[mid] < key)   min  = mid + 1;
            else if (data[mid] > key)   max  = mid - 1;
            else /* (data[mid] = key)*/ break;
        }

        var pad = function(n) { return (' '+n).slice(-2); }

        console.log( "key: %s, min: %d, mid: %d, max: %s,  mid<num:"
            ,pad(key), min, mid, pad(max), (mid<num)|0 );

        return -1; // KEY_NOT_FOUND
    }
```

Running `BinSearchPrint()` on `data` we get:

```
key: -1, min: 0, mid: 0, max: -1,  mid<num: 1
key:  0, min: 0, mid: 0, max: -1,  mid<num: 1
key:  1, min: 0, mid: 0, max:  1,  mid<num: 1
key:  2, min: 1, mid: 1, max:  0,  mid<num: 1
key:  3, min: 1, mid: 1, max:  1,  mid<num: 1
key:  4, min: 2, mid: 1, max:  1,  mid<num: 1
key:  5, min: 0, mid: 2, max:  5,  mid<num: 1
key:  6, min: 3, mid: 3, max:  2,  mid<num: 1
key:  7, min: 3, mid: 3, max:  3,  mid<num: 1
key:  8, min: 4, mid: 3, max:  3,  mid<num: 1
key:  9, min: 3, mid: 4, max:  5,  mid<num: 1
key: 10, min: 5, mid: 5, max:  4,  mid<num: 0
key: 11, min: 5, mid: 5, max:  5,  mid<num: 0
key: 12, min: 6, mid: 5, max:  5,  mid<num: 0
```


## Advanced Binary Search C Code

```c
int BinSearchLessThanEqual( int key, const int size, int data[] )
{
    const int num = size - 1;
    /* */ int min = 0;
    /* */ int max = num;
    // var max = data.length - 1; // Javascript, Java conversion

    while( min <= max )
    {
        int mid = min + ((max - min) / 2);

        /**/ if (data[mid] < key)   min  = mid + 1;
        else if (data[mid] > key)   max  = mid - 1;
        else /* (data[mid] = key)*/ return mid    ;
    }

    if( max < 0 )
        return 0;  // key < data[0]
    else
    if( min > num )
        return -1; // key >= data[ num ] // KEY_NOT_FOUND
    else
        return (min < max)
            ? min
            : max + 1;
}

int BinSearchLessThanEqualOrLast( int key, const int size, int data[] )
{
    const int num = size - 1;
    /* */ int min = 0;
    /* */ int max = num;
    // var max = data.length - 1; // Javascript, Java conversion

    while( min <= max )
    {
        int mid = min + ((max - min) / 2);

        /**/ if (data[mid] < key)   min  = mid + 1;
        else if (data[mid] > key)   max  = mid - 1;
        else /* (data[mid] = key)*/ return mid    ;
    }

    if( max < 0 )
        return 0;     // key < data[0]
    else
    if( min > num )
        return num; // key >= data[ size-1 ]
    else
        return (min < max)
            ? min
            : max + 1;
}

int BinSearchGreaterThen( int key, const int size, int data[] )
{
    const int num = size - 1;
    /* */ int min = 0;
    /* */ int max = num;

    while( min <= max )
    {
        // To convert to Javascript:
        // var mid = min + ((max - min) / 2) | 0;
        int mid = min + ((max - min) / 2);

        /**/ if (data[mid] < key) min = mid + 1;
        else if (data[mid] > key) max = mid - 1;
        else return                     mid + 1;
    }

    if( max < 0 )
        return 0;   // key < data[0]
    else
    if( min > num )
        return num; // key >= data[ size-1 ]
    else
        return (min < max)
            ? min + 1
            : max + 1;
}
```

Corresponding Javascript versions:

```Javascript
// ==================================================
function BinSearch( key, data )
{
    var num = data.length - 1;
    var min = 0;
    var max = num;

    while( min <= max )
    {
        var mid = min + ((max - min) / 2) | 0;

        /**/ if (data[mid] < key)   min  = mid + 1;
        else if (data[mid] > key)   max  = mid - 1;
        else /* (data[mid] = key)*/ return mid    ;
    }

    return -1; // KEY_NOT_FOUND
}

// ==================================================
function BinSearchLessThanEqual( key, data )
{
    var num = data.length - 1;
    var min = 0;
    var max = num;

    while( min <= max )
    {
        var mid = min + ((max - min) / 2) | 0;

        /**/ if (data[mid] < key)   min  = mid + 1;
        else if (data[mid] > key)   max  = mid - 1;
        else /* (data[mid] = key)*/ return mid    ;
    }

    if( max < 0 )
        return 0;  // key < data[0]
    else
    if( min > num )
        return -1; // key >= data[ num ] // KEY_NOT_FOUND
    else
        return (min < max)
            ? min
            : max + 1;
}

// ==================================================
function BinSearchLessThanEqualOrLast( key, data )
{
    var num = data.length - 1;
    var min = 0;
    var max = num;

    while( min <= max )
    {
        var mid = min + ((max - min) / 2) | 0;

        /**/ if (data[mid] < key)   min  = mid + 1;
        else if (data[mid] > key)   max  = mid - 1;
        else /* (data[mid] = key)*/ return mid    ;
    }

    if( max < 0 )
        return 0;     // key < data[0]
    else
    if( min > num )
        return num; // key >= data[ size-1 ]
    else
        return (min < max)
            ? min
            : max + 1;
}

// ==================================================
function BinSearchGreaterThen( key, data )
{
    var num = data.length - 1;
    var min = 0;
    var max = num;

    while( min <= max )
    {
        // var mid = min + ((max - min) / 2) | 0;
        var mid = (min + ((max - min) / 2)) | 0;

        /**/ if (data[mid] < key)   min  = mid + 1;
        else if (data[mid] > key)   max  = mid - 1;
        else /* (data[mid] = key)*/ return mid + 1;
    }

    if( max < 0 )
        return 0;   // key < data[0]
    else
    if( min > num )
        return num; // key >= data[ size-1 ]
    else
        return (min < max)
            ? min + 1
            : max + 1;
}
```


# References:

The stack overflow question that started it all and my original answer:

* [modify binary search to find the next bigger item than the key](https://stackoverflow.com/questions/16219998/modify-binary-search-to-find-the-next-bigger-item-than-the-key/28309550#28309550)
* [Beautiful Code](https://www.amazon.com/Beautiful-Code-Leading-Programmers-Practice/dp/0596510047/)
* (Three Beautiful Quicksorts)[https://www.youtube.com/watch?v=QvgYAQzg1z8)
