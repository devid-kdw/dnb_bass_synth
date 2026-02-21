import sys

def extract_pdf(path):
    try:
        import pypdf
        with open(path, 'rb') as f:
            reader = pypdf.PdfReader(f)
            text = '\n'.join([page.extract_text() for page in reader.pages])
            print(f"--- {path} ---\n{text}\n")
    except ImportError:
        try:
            import PyPDF2
            with open(path, 'rb') as f:
                reader = PyPDF2.PdfReader(f)
                text = '\n'.join([page.extract_text() for page in reader.pages])
                print(f"--- {path} ---\n{text}\n")
        except ImportError:
            try:
                import fitz
                doc = fitz.open(path)
                text = '\n'.join([page.get_text() for page in doc])
                print(f"--- {path} ---\n{text}\n")
            except ImportError:
                print(f"Failed to find python pdf libraries for {path}. Try osx strings or something.")

if __name__ == "__main__":
    extract_pdf(sys.argv[1])
    extract_pdf(sys.argv[2])
