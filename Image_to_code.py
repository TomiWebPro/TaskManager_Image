from PIL import Image

# Load the image (image.jpg or image.png)
image_path = "image.jpg"
img = Image.open(image_path)

# Function to convert an image to absolute grayscale


def absolute_grayscale(img):
    img = img.convert("L")  # Convert to grayscale
    img = img.point(lambda x: 0 if x < 128 else 255, "1")  # Binarize
    return img


# Get user input for resolution
resolution = input("Enter resolution (e.g., 4x4): ").split('x')
resolution_x, resolution_y = int(resolution[0]), int(resolution[1])

# Convert the image to absolute grayscale
gray_img = absolute_grayscale(img)

# Get the size of the output image based on user-defined resolution
output_width = resolution_x
output_height = resolution_y

# Resize the grayscale image to the desired resolution
gray_img = gray_img.resize((output_width, output_height), Image.ANTIALIAS)

# Save the grayscale image as 'output_image.png'
output_path = 'output_image.png'
gray_img.save(output_path)

# Print the pixel values (optional)
for y in range(output_height):
    row = []
    for x in range(output_width):
        pixel = gray_img.getpixel((x, y))
        row.append(pixel)
    print(row)

# Print the pixel values in the specified format
print()
print("int shouldRunList[] = {")
for y in range(output_height):
    row = []
    for x in range(output_width):
        pixel = gray_img.getpixel((x, y))
        row.append(pixel)
    print("    " + ", ".join(str(value) for value in row) + ",")
print("};")

print(f"Output image saved as {output_path}")
