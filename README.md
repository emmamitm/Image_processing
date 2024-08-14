# Image Filter Removal and Comparison Tool
Image Processing written by Emma Mitchell
<img width="1247" alt="image" src="https://github.com/user-attachments/assets/5b921b3e-de90-49a0-b107-bd754dec7cd0">
## Project Overview
This project is designed to process images by removing color filters through direct manipulation of bits and pixels. Once the filters are removed, the tool runs tests to compare the original and processed images, ensuring accuracy and effectiveness.

## Key Features
- **Filter Removal**: The tool directly manipulates image data at the pixel level to strip away unwanted color filters.
- **Image Comparison**: After processing, the tool compares the original and filter-free images to assess the success of the filter removal process.

## Classes and Methods

### ImageProcessor
- **removeFilter(image)**: Takes an image as input and removes color filters by adjusting the pixel data. This method uses bitwise operations to achieve precise control over the image's color channels.

### ImageComparator
- **compareImages(original, processed)**: Compares the original and processed images, focusing on pixel-level differences. The method generates a report indicating the effectiveness of the filter removal.

## Why This Implementation Stands Out
My implementation excels in precision and efficiency. By working directly with the bits and pixels, the tool offers fine-grained control over image processing, resulting in high-quality, filter-free images. The comparison method ensures that the tool's effectiveness is rigorously tested, making it a reliable solution for anyone looking to remove color filters from images. 
