#include"prefix_match_search.h"

int collect_prefix_matches(
    char * const *bins,
    int n,
    const char *prefix,
    char ***out_matches,
    int *out_count
)
{
    if (!out_matches)
      {
        return -1;
      }
    *out_matches = NULL;    
    if (out_count)
      *out_count = 0;


    if (!bins || n < 0 || !prefix)
      {
        return -1;
      }

    size_t prefix_len = strlen(prefix);

    //handle empty prefix
    if (prefix_len == 0)
      {
        char **result = NULL;
        if (n > 0)
	  {
            result = malloc(n * sizeof(char *));
            if (!result) return -1;
            for (int i = 0; i < n; ++i)
	      {
                result[i] = bins[i];
	      }
	  }
        *out_matches = result;
        if (out_count) *out_count = n;
        return 0;
    }

    //binary search for first candidate
    int low = 0, high = n;
    while (low < high)
      {
        int mid = low + (high - low) / 2;
        int cmp = strncmp(bins[mid], prefix, prefix_len);
        if (cmp < 0)
	  {
            low = mid + 1;
	  }
	else
	  {
            high = mid;
	  }
      }

    int start = low;
    int count = 0;

    //count consecutive matches from start
    for (int i = start; i < n; ++i)
      {
        if (strncmp(bins[i], prefix, prefix_len) == 0)
	  {
            ++count;
	  }
	else
	  {
            break;
	  }
      }

    char **result = NULL;
    if (count > 0)
      {
        result = malloc(count * sizeof(char *));
        if (!result)
	  {
	    fprintf(stderr,"smenu error: malloc failed at prefix searching...\n");
            return 0; 
	  }
        for (int i = 0; i < count; ++i)
	  {
            result[i] = bins[start + i];
	  }
      }

    *out_matches = result;
    if (out_count) *out_count = count;
    return 1;
}
