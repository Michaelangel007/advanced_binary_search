    #include <stdio.h>

    enum { KEY_NOT_FOUND = -1 };

    /* @param needle   What to look for,
       @param size     Array size; 1 past the last element,
       @param haystack The sorted array to search in.
    */
    // ==================================================
    int BinSearch( int key, int size, int *data )
    {
        int min = 0;
        int max = size - 1;

        while (min <= max)
        {
            int mid = min + ((max - min) / 2);

            /**/ if (data[mid] < key)   min  = mid + 1;
            else if (data[mid] > key)   max  = mid - 1;
            else /* (data[mid] = key)*/ return mid;
        }
        return KEY_NOT_FOUND;
    }

    const char *STATUS[2] =
    {
        "FAIL",
        "pass"
    };

    // ==================================================
    int main()
    {
        int data[] = { 1, 3, 5, 7, 9, 11 };
        int size = sizeof( data ) / sizeof( data[0] );
        for (int i = 0; i < size; ++i )
        {
            int at = BinSearch( data[i], size, data );
            int pass = (data[at] == data[i]);

            printf( "Searching for %2d IN the array ... ", data[i] );
            printf( "result @ [%+2d] ", at );
            printf( "%s\n", STATUS[ pass ] );
        }

        for (int i = 0; i <= 12; i += 2)
        {
            int at = BinSearch( i, size, data );
            int pass = (at == -1);

            printf( "Searching for %2d NOT in array ... ", i );
            printf( "result @ [%+2d] ", at );
            printf( "%s\n", STATUS[ pass ] );
        }

        return 0;
    }
