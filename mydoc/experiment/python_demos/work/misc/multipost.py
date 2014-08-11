#!/usr/bin/python
import base64
import itertools
import mimetools
import mimetypes
import urllib
import urllib2
import sys

#Post form data or file through form.

class MultiPartForm(object):
    """Accumulate the data to be used when posting a form."""

    def __init__(self):
        self.form_fields = []
        self.files = []
        self.boundary = mimetools.choose_boundary()
        return

    def get_content_type(self):
        return 'multipart/form-data; boundary=%s' % self.boundary

    def add_field(self, name, value):
        """Add a simple field to the form data."""
        self.form_fields.append((name, value))
        return

    def add_file(self, fieldname, filename, mimetype=None):
        """Add a file to be uploaded."""
        body = open(filename, "rb").read()
        if mimetype is None:
            mimetype = (mimetypes.guess_type(filename)[0]
                         or
                         'application/octet-stream'
                         )
        self.files.append((fieldname, filename, mimetype, body))
        return

    def __str__(self):
        """Return a string representing the form data,
        including attached files.
        """
        # Build a list of lists, each containing "lines" of the
        # request.  Each part is separated by a boundary string.
        # Once the list is built, return a string where each
        # line is separated by '\r\n'. 
        parts = []
        part_boundary = '--' + self.boundary

        # Add the form fields
        parts.extend(
            [ part_boundary,
              'Content-Disposition: form-data; name="%s"' % name,
              '',
              value,
            ]
            for name, value in self.form_fields
            )

        # Add the files to upload
        parts.extend([
            part_boundary,
            'Content-Disposition: file; name="%s"; filename="%s"' % \
               (field_name, filename),
            'Content-Type: %s' % content_type,
            '',
            body,
          ]
          for field_name, filename, content_type, body in self.files
          )

        # Flatten the list and add closing boundary marker, and
        # then return CR+LF separated data
        flattened = list(itertools.chain(*parts))
        flattened.append('--' + self.boundary + '--')
        flattened.append('')
        return '\r\n'.join(flattened)

def form_submitwrt610(ipAddr):
    # Create the form with simple fields
    form = MultiPartForm()

    # Form params and value.
    form.add_field('submit_button', 'Restore')
    form.add_field('small_screen', '')
    form.add_field('wait_time', '25')

    # The file to be submit by form.
    form.add_file('restore', 'WRT160Nv3_v3.0.02.cfg')

    # Build the request
    request = urllib2.Request('http://'+ ipAddr +'/restore.cgi')
    authheader = "Basic %s" % base64.encodestring('%s:%s' % ("admin", "admin"))[:-1]
    body = str(form)
    request.add_header("Authorization", authheader)
    request.add_header('Content-type', form.get_content_type())
    request.add_header('Content-length', len(body))
    request.add_data(body)

    #print
    #print 'OUTGOING DATA:'
    #print request.get_data()

    try:
        res = urllib2.urlopen(request)
        #print
        #print 'SERVER RESPONSE:'
        #print res.read()
    except IOError, e:
        print "It looks like the username or password is wrong."
        sys.exit(1)

def form_submite3000(ipAddr):
    # Create the form with simple fields
    form = MultiPartForm()

    # Form params and value.
    form.add_field('submit_button', 'Restore')
    form.add_field('small_screen', '')
    form.add_field('wait_time', '25')

    # The file to be submit by form.
    form.add_file('restore', 'Linksys_E3000V1_v1.0.01.cfg')

    # Build the request
    request = urllib2.Request('http://'+ ipAddr +'/restore.cgi')
    authheader = "Basic %s" % base64.encodestring('%s:%s' % ("admin", "admin"))[:-1]
    body = str(form)
    request.add_header("Authorization", authheader)
    request.add_header('Content-type', form.get_content_type())
    request.add_header('Content-length', len(body))
    request.add_data(body)

    #print
    #print 'OUTGOING DATA:'
    #print request.get_data()

    try:
        res = urllib2.urlopen(request)
        #print
        #print 'SERVER RESPONSE:'
        #print res.read()
    except IOError, e:
        print "It looks like the username or password is wrong."
        sys.exit(1)

if __name__ == '__main__':
    form_submite3000('172.168.1.15')
