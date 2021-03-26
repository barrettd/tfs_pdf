# tfs_pdf
Simple, quick PDF writer.  

Not full featured, but sufficient for generating forms and text documents.

Supports boxes (hollow and filled), circles (hollow and filled), lines, polylines, text.

Supported fonts include: Times, Courier, Helvetica, Symbol and ZapfDingbats.

Look to the UnitTest for an example of use.

* Generally you create a TFSPdfDocument, then fill it with text, lines, boxes or whatever.
* Then you create a TFSPdfWriter, given a file name.  
* Then you stream the document to the writer: e.g.  writer << document;

Have fun.  Let me know if you enjoy the PDF project or if you find bugs or need additional features.

Regards,
Barrett Davis
Tree Frog Software


