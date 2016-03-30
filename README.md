# calc
Simple calculator

This simple calculator takes after `bc` but provides only a basic subset of `bc`'s capabilities.

You may or may not care about the following decisions I have made:
<ul>
  <li>
    log has been turned into the infix operator |, where (number)|(base) is the syntax
  </li>
  <li>
    Parenthesized operations adjacent to literals or other parenthesized operations will assume multiplication if an operator is not
    present
  </li>
  <li>
    The error messages choose to be less mathematically helpful in favor of being helpful for the dev (me) in debugging
  </li>
</ul>
