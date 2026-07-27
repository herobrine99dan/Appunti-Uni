var mainTitleColor = '"#D95F0E"';
var sectionHeaderColor = '"#993404"';
var navTableBGColor = '"#FED98E"';

function editContents(id, contents, append)
{
    let x = document.getElementById(id);
    if (x !== null)
    {
        if (append)
            x.innerHTML += contents;
        else
            x.innerHTML = contents;
    }
}

function topOfPageTable(pathToRoot)
{
	document.write('<center><h1><font color=' + mainTitleColor + '>Moving From Java to C++</font></h1></center>');
}

// return value is what you write, if anything, to close the tag
function openFileTag(pathToRoot, currentRef, pathFromRootToAnchorRef, anchorRef)
{
	if ((currentRef == anchorRef) || ((currentRef == "") && (anchorRef == "index.html")))
	{
		document.write('<b>');
		return '</b>';
	}
	document.write('<a href="' + pathToRoot + pathFromRootToAnchorRef + anchorRef + '">');
	return '</a>';
}

function navigationTable(pathToRoot)
{
	fName = window.location.href.substring(window.location.href.lastIndexOf("/")+1,
		window.location.href.length);
	document.write('<ul style="padding-left:15px">');

	document.write('<li style="margin-bottom:1em">');
	closeTag = openFileTag(pathToRoot, fName, "", "JavaToC++.html");
	document.write('Home' + closeTag + '</li>');

	document.write('<li style="margin-bottom:1em">');
	closeTag = openFileTag(pathToRoot, fName, "./", "Similarities.html");
	document.write('Similarities' + closeTag + '</li>');

	document.write('<li style="margin-bottom:1em">');
	closeTag = openFileTag(pathToRoot, fName, "./", "Arrays.html");
	document.write('Arrays' + closeTag + '</li>');

	document.write('<li style="margin-bottom:1em">');
	closeTag = openFileTag(pathToRoot, fName, "./", "KeyboardScreenIO.html");
	document.write('Keyboard/Screen I/O' + closeTag + '</li>');

	document.write('<li style="margin-bottom:1em">');
	closeTag = openFileTag(pathToRoot, fName, "./", "IdentifiersAtGlobalScope.html");
	document.write('Identifiers at global scope' + closeTag + '</li>');

	document.write('<li style="margin-bottom:1em">');
	closeTag = openFileTag(pathToRoot, fName, "./", "ParameterPassing.html");
	document.write('Parameter passing' + closeTag + '</li>');

	document.write('<li style="margin-bottom:1em">');
	closeTag = openFileTag(pathToRoot, fName, "./", "CharacterStrings.html");
	document.write('Character strings' + closeTag + '</li>');

	document.write('<li style="margin-bottom:1em">');
	closeTag = openFileTag(pathToRoot, fName, "./", "FileIO.html");
	document.write('File I/O' + closeTag + '</li>');

	document.write('<li style="margin-bottom:1em">');
	closeTag = openFileTag(pathToRoot, fName, "./", "Classes.html");
	document.write('Classes' + closeTag + '</li>');

	document.write('<li style="margin-bottom:1em">');
	closeTag = openFileTag(pathToRoot, fName, "./", "StackAllocatedObjects.html");
	document.write('Stack-allocated objects' + closeTag + '</li>');

	document.write('<li style="margin-bottom:1em">');
	closeTag = openFileTag(pathToRoot, fName, "./", "StackAllocatedArrays.html");
	document.write('Stack-allocated arrays' + closeTag + '</li>');

	document.write('<li style="margin-bottom:1em">');
	closeTag = openFileTag(pathToRoot, fName, "./", "SeparateCompilation.html");
	document.write('Separate compilation' + closeTag + '</li>');

	document.write('<li style="margin-bottom:1em">');
	closeTag = openFileTag(pathToRoot, fName, "./", "BasicPointerUse.html");
	document.write('Basic Pointer Use' + closeTag + '</li>');

	document.write('<li style="margin-bottom:1em">');
	closeTag = openFileTag(pathToRoot, fName, "./", "MemoryManagement.html");
	document.write('Memory management' + closeTag + '</li>');

	document.write('<li style="margin-bottom:1em">');
	closeTag = openFileTag(pathToRoot, fName, "./", "SomeCookbookMappings.html");
	document.write('Some cookbook mappings' + closeTag + '</li>');

	document.write('</ul>');
}

function navigationTableTD(pathToRoot)
{
	document.write('<table align="left" style="padding-right:1em"><tr>');
	document.write('<td valign="top" bgcolor=' + navTableBGColor + '>');
	navigationTable(pathToRoot);
	document.write('</td></tr></table>');
}

function sectionHeader(header)
{
	document.write('<h2><font color=' + sectionHeaderColor + '>' + header + '</font></h2>');
}

// A version that should not be used because document.write can be abused.
// Use signAndDatePageText instead.
function signAndDatePage(pathToRoot)
{
	document.write('<hr />');
	document.write('<img src="' + pathToRoot + 'images/ku_jayhawk.png" align="right" />');
	document.write('<p><font size="-2">James R. Miller (<a href="mailto:jrmiller@ku.edu">jrmiller@ku.edu</a>) &ndash;&nbsp;');
	document.write("Page last modified: " + document.lastModified + "</font></p>");
}

function signAndDatePageText(pathToRoot)
{
    "use strict";
    return '<hr /> <img src="' + pathToRoot + 'images/ku_jayhawk.png" align="right" />' +
    '<p><font size="-2">James R. Miller (<a href="mailto:jrmiller@ku.edu">jrmiller@ku.edu</a>) &ndash;&nbsp;' +
    'Page last modified: ' + document.lastModified + '</font></p>';
}
