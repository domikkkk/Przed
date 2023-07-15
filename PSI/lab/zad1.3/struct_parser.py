# Krzysztof Stawarski
# Laboratorium PSI Zadanie 1
# 30.03.2023
from typing import Tuple, List


class InvalidFieldTypeException(Exception):
    pass


def split_name(name) -> Tuple[str, int]:
    """
    "myArray[123]" -> "myArray",123
    """

    symbol, count = name.split("[")
    return symbol, int(count[:-1])


def parse_struct(struct_string: str) -> Tuple[str, List[str]]:
    """
    Parses incoming C struct, returns list of all field types
    (this can be joined for valid struct format) and array of field names
    """

    # conversion between C mnemonics and python struct module
    # from struct documentation
    types_map = {
        "char": "c",
        "signed char": "b",
        "unsigned char": "B",
        "short int": "h",
        "unsigned short int": "H",
        "int": "i",
        "unsigned int": "I",
        "long int": "q",
        "unsigned long int": "Q",
        "long long int": "q",
        "unsigned long long int": "Q",
        "ssize_t": "n",
        "size_t": "N",
        "float": "f",
        "double": "d",
        "void*": "p",
    }

    field_types = []
    field_names = []

    # extracts the part between brackets
    fields = struct_string.split("{")[1][:-1]
    # get definitions of fields, between colons
    tokens = fields.split(";")[:-1]

    for token in tokens:
        token = token.strip()
        parts = token.split(" ")
        ctype, name = " ".join(parts[:-1]), parts[-1]
        if ctype not in types_map:
            ctype += " int"
            if ctype not in types_map:
                raise InvalidFieldTypeException(f"Unknown type '{ctype}'")

        if name[-1] == "]":
            # array type, need to extract the element count
            name, element_count = split_name(name)
            field_types.append((str(element_count), types_map[ctype]))
        else:
            field_types.append(types_map[ctype])
        field_names.append(name)

    return field_types, field_names


# parse_struct("struct {long int a; short int b; char c[10];}")
