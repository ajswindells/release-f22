/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{
    if (s.size() == 0) {
        return 0;
    }
    T temp = s.top();
    s.pop();
    double total = temp + sum(s);
    s.push(temp);
    return total;
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
    stack<char> s;
    while (!(input.empty())) {
    if (input.front() == '[') {
        s.push('[');
    }
    if (input.front() == ']') {
        if (s.empty()) {
            return false;
        }
        s.pop();
    }
    input.pop();
    }
    return s.empty();
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    
    int opcounter = q.size();
    int blocksize = 1;
    while(opcounter != 0)
    {
        int min = (opcounter < blocksize)? opcounter : blocksize;
        if (blocksize%2 == 0)
        {
            //reverse
            for (int i = 0 ; i < min; i++)
            {
                //pop from queue push to stack
                T temp = q.front();
                q.pop();
                s.push(temp);
            }
            for (int i = 0; i < min; i++)
            {
                //pop from stack push to queue
                T temp = s.top();
                s.pop();
                q.push(temp);
            }
        }
        else
        {
            //same order
            for (int i = 0; i < min; i++)
            {
                //push to end of queue
                T temp = q.front();
                q.pop();
                q.push(temp);
            }
        }
        opcounter -= min;
        blocksize++;
}
}
}
