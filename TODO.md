# Todo Items

1. Document build issues for tesseract 4.0 on different platforms.

1. Get this working on Windows.

1. Example for GetSmudges

1. Check GetBoxes returns what BoundingBoxes used to.

1. ReadConfigFile(api, "tests/debug_config") terminates if the file has errors.
  try sliding in definition of exit() in Rexit/exit.c

  library(Rtesseract); api = tesseract(); ReadConfigFile(api, "Experiments/bad_config")

1. tprintf() and messages on console.

1. Be able to interrupt in OCR computations with Ctrl-c.

1. [Verify sane] Get alternatives is returning different output between:
 ```r
 library(Rtesseract)
 f = system.file("images", "OCRSample2.png", package = "Rtesseract")
 a = getAlternatives(f)

 api = tesseract(f)
 Recognize(api)
 ri = as(api, "ResultIterator")
 b = lapply(ri, getAlternatives, "word")
 identical(a, b)

 api = tesseract(f)
 Recognize(api)
 ri = as(api, "ResultIterator")
 b = lapply(ri, getNativeSymbolInfo("getAlts"), "word")
 ```


1. [yes] Does the ResultIterator get released?

1. Do we need to delete the choice object

1. Test that plot/other helper functions are still functioning with output from the getXXX functions.
Fix the names on the bounding boxes to be consistent within the package and with the PDF tables code.
Clean up ocr() so that the bounding box is returned, is consistent with that from BoundingBoxes
 and creates a data frame/matrix.

1. Update documentation/NAMESPACE to reflect current functions and functionality.

1. ? Other methods form the baseapi.h ?

1. [can we reproduce this] seg fault in plotSubImage() when run via the examples.
  [Seems okay on OSX machine (DTL)]
  Could be an earlier example with memory issues appearing at this point.
  e.g. pixRead()

1. [check] Rationalize tesseract() and Init() so can pass all the arguments through to Init()

1. [test] Have an option for SetInputName() to read the image and load it via SetImage().

1. [change name of function] How can we query whether we have to call Recognize() or not?
              hasRecognized() function - Change name
                 Ask for a ResultIterator and if it returns NULL, then call Recognize().


1. GetInputImage() - figure out how to convert the Pix to an array() in R 
     deal with the bits and mapping them back to what we expect from, e.g., readPNG(),
     [fixed] an array is returning 32 deep, whereas readPNG() is just 4.  The depth is in bits in Pix (leptonica).


1. [very low priority] Sort out the R renderer class.
  Why do we want to have our own?  If we have to use ProcessPages() we don't want to write to disk unnecessarily.


1. [don't make it accessible from the tesseract object]
  When we return a Pix, increase the reference count and put a finalizer to decrease it.
    The destroyPix  seems to be there.

1. [dont expose it to end-user] Also if we have a ResultIterator, don't let the tesseract instance die/
 ?Should we introduce  a sub-class of tesseract with which we can solve these and the already Recognize()d issues?

1. When tesseract complains below, raise an error.  Stop the output going to stdout/stderr
 (see tprintf_internal issue above. )
      The error messages run through tprintf_internal() in ccutil/tprinf.cpp.
      There is a debug_file that we can write to.  Set this and then read that file when there is an error. Very ugly.
      How do people do this in python, etc.
  Error opening data file /Users/duncan/Projects/OCR/tesseract-ocr/tessdata/osd.traineddata
  Please make sure the TESSDATA_PREFIX environment variable is set to the parent directory of your "tessdata" directory.
  Failed loading language 'osd'
  Tesseract couldn't load any languages!

1. How do we regenerate this?
   Unset TESSDATA_PREFIX in ~/.cshrc and run Rtesseract.
       api = tesseract("inst/trainingSample/eng.tables.exp0.png", 0L)

 This is what did it - but not anymore.
  Sys.setenv(TESSDATA_PREFIX= path.expand("~/Projects/OCR/tesseract-ocr"))
  library(Rtesseract)
   api = tesseract("inst/trainingSample/eng.tables.exp0.png", 0L)
   Recognize(api)


1. Connect to OpenCV for manipulating the image.  perhaps thresholding away the specs. 
    https://github.com/swarm-lab/videoplayR
    https://code.google.com/archive/p/r-opencv/source/default/source


1. ?? GetInputName seems to take an age (in some cases)!!  Did time it and got exactly 0.

1. ?? plot.OCR() seems to be doing something unnecessary - an extra call to Recognize() somewhere?
   Seems okay.  rasterImage() and readPNG() do take time.

1. [not really relevant] See MutableIterator for possibly modifying the tesseract content.
  This is just a live ResultIterator that has access to the contents of the TessBaseAPI so we could change them.

1. [okay now] Can't seem to open pdf config file - i.e., the one called pdf in /usr/local/share/tessdata/configs, but can find batch.nochop.

1. [check] 
 With cropBoxes, can get negative indices.
  Change the margin.  Compute it so that it can't yield negative indices.


1. compareWords() warns about different lengths. Something wrong? See MarkLundy/ocr.R
  Is this to be expected as the ocr and truth words may have different number of characters.
  Or think of other ways to compare them - adist?

1. [check] ocr() function using the API-level functions.
 ACTUALLY, just remove and use getAlternatives(), getConfidences(), getBoxes(), getText().
   i.e. implement not in C but in R code to assemble the different pieces.
   Can do now.

1. [Mostly done]   Color code the rectangles for the bboxes according to the confidence.

1. Annotate an SVG plot of this so that we can see the confidence levels and alternatives for a bbox.

1. [Feature Request] When find an error in the OCR, get the subset of the image for that bounding box and 
   then see if we can cluster them.
    Need to know if it is an error, so presumably need to know truth.
    Or instead of errors, just those values with low confidence.
    See inst/caseStudies

  Can do this from the bounding box information and reading the image using one of the R packages.

1. [ok] error rates and confusion matrix when know the actual values.

1. [low] Get components - leptonica objects Boxa and Pixa
   How about identifying lines.  Done in bounding box if we use psm_auto for PageSegmentationMode

1. [Check] Get alternatives via R interface to API, not the R_tesseract_ alternatives routine.
   Is this in the ocr() routine? e.g. ocr(, alternatives = TRUE)


_______________________________________

# Done

+ [done] ProcessPages in render.cpp

+ [done - changed to upper to match API] ??Change the names of the functions to initial lower case, e.g. getInputName(), ?

+ [Done] Plot the image and the components and show the confidence level for each  box
   See tests/plot.R
   
+ [done] switch getAlternatives() method for TessBaseAPI to use ResultIterator method.
+ [done] getAlternatives(ri) may not want to just get the alternatives for the current cursor in the iterator, but all of them.

+ [resolved] Additionally, seems to be returing alternatives at the wrong level (Returns a single letter, only the first letter) 
  Does ChoiceIterator() only work for characters/symbols, not words.
  - need to check that this is operating correctly.
   This is because we never call Next(), but lapply(ri, fun, level) does. And we have to specify the
   level here.
   
+ [Done] GetAlternatives - use getAlternatives
    + Only returns one
    + Segfaults.
    + Look at the R_ocr_alternatives and see if we can reuse that code.
    + Note that ocr(alternatives = TRUE) works.
   

+ [done] create searchable pdf - use their renderer
  want to be able to fix the errors and then create it.
  Started in example in pdf.R and code in render.cpp.
     It generates a pdf but it cannot be opened.  
   Needed a finalizer on the R object to call the destructor to close the file.


+ [resolved - ocr removed] Test that output is the same and correct between ocr and getXXX functions.

+ [done] Make function calls consistent (getXXX to GetXXX)
+ [done] remove the ocr() function
+ [done] Add an example for lapply.Rd with an R function.
+ [done] Merge tesseractFuns.Rd
+ [done from NAMESPACE] remove the ocr() function
+ [done] readImage not being found in plot.OCR() - .Rbuildignore was causing it to be discard due to FUNS. Matching is case-insensitive.
+ [done] Document SetInputName, SetImage

+ [done] Remove GetIterator.Rd

+ [fixed] Segfaults if Recognize hasn't been called.
 library(Rtesseract)
 ts = tesseract(system.file("trainingSample", "eng.tables.exp0.png", package = "Rtesseract"))
 a = getAlternatives(ts)

+ [Fixed now] Investigate  "Calling Recognize again"
 ```r
  library(Rtesseract)
  ts = tesseract(system.file("trainingSample", "eng.tables.exp0.png", package = "Rtesseract"))
  b = getBoxes(ts)
 ```


+ [done] SetInputName - if no api, warn don't treat file name as api.

+ [Doesn't do better] Use the cube - Init() with an engineMode

+ [Fixed] read_params_file
          read_params_file: Can't open NA

+ [Fixed] Why does cmd-line tesseract give a different set of words as ocr()
  What about 
    ts = tesseract(fs)
    getConfidences(ts)
    The PageSegMode was being reset in the API::Init() method and we were setting it before calling that.


+ [done] get information about the current image - dimensions, other info. See getImageInfo() & getImageDims()

+ [Done] See getConfidences() on a tessseract object.  Get the confidences separately from ocr().

+ [Done] Give a blank image (i.e. a file that contains nothing) and ocr() seg faults
   created via PDFBox w/o the jbig2-imageio in the classpath
   To create one, in DSIProjects/MarkMundy, 
      java -jar ~/Downloads/pdfbox-app-2.0.2.jar PDFToImage -outputPrefix test -imageType png 1982-128-44.pdf 

+ [Done] Check if we have support for a particular image based on its type.
  Check the supported leptonica image formats.

+ [Done] cropToBoxes = TRUE in plot.OCR - get it to work.

+ [Done] When Recognize() not called, don't seg fault in lapply().

+ [Done] SetVariable and GetVariable.
     tests/vars.R
     different types.

+ [Basic] configuration

+ [Done] capabilities  - at configure time.
  e.g. image formats leptonica understands.
   leptonicaImageFormats()

+ [Done] PrintVariables scan() problem.
    Error during wrapup: line 376 did not have 3 elements
    Yet
       tt = readLines(f)
       els = strsplit(tt, "\t")
       sapply(els, length)
+ [fixed] If the file doesn't exist, get a weird  error message.

+ [Done] Make getCharWidth/Height ignore text with no content & just one space.


# Other

+ Session generating error about not being able to read osd.traineddata.

 ```r
16> api = tesseract("inst/trainingSample/eng.tables.exp0.png")
17> .Call("R_TessBaseAPI_SetPageSegMode", api, 0L)
[1] TRUE
18> Recognize
*** output flushed ***
19> Recognize(api)
Error opening data file /Users/duncan/Projects/OCR/tesseract-ocr/tessdata/osd.traineddata
Please make sure the TESSDATA_PREFIX environment variable is set to the parent directory of your "tessdata" directory.
Failed loading language 'osd'
Tesseract couldn't load any languages!
Warning: Auto orientation and script detection requested, but osd language failed to load
[1] TRUE
20> .Call("R_TessBaseAPI_SetPageSegMode", api, 1L)
[1] TRUE
21> Recognize(api)
Error opening data file /Users/duncan/Projects/OCR/tesseract-ocr/tessdata/osd.traineddata
Please make sure the TESSDATA_PREFIX environment variable is set to the parent directory of your "tessdata" directory.
Failed loading language 'osd'
Tesseract couldn't load any languages!
Warning: Auto orientation and script detection requested, but osd language failed to load
[1] TRUE
22> .Call("R_TessBaseAPI_SetPageSegMode", api, 2L)
[1] TRUE
```


