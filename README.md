# qsreplace

[tomnomnom/qsreplace](https://github.com/tomnomnom/qsreplace)

## Replace all query string values

```
▶ cat urls.txt | qsreplace TEEXT
https://example.com/path?one=TEEXT&two=TEEXT
```

## Replace query string values by param_name

```
▶ cat urls.txt | qsreplace one TEEXT
https://example.com/path?one=TEEXT&two=1
```
