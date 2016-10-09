package group.gld3d.android.gld3d_gps_logger;

import android.content.Context;
import android.content.Intent;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.net.Uri;
import android.os.Environment;
import android.provider.Settings;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.appindexing.Action;
import com.google.android.gms.appindexing.AppIndex;
import com.google.android.gms.common.api.GoogleApiClient;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.Calendar;
import java.util.GregorianCalendar;

public class GPS_Mornitoring_View extends AppCompatActivity implements LocationListener {
    private LocationManager locationManager;
    /**
     * ATTENTION: This was auto-generated to implement the App Indexing API.
     * See https://g.co/AppIndexing/AndroidStudio for more information.
     */
    private GoogleApiClient client;
    private Boolean bRecording = Boolean.FALSE;
    private File    fLogFile;
    private FileOutputStream    fOutStream;
    private OutputStreamWriter  outStreamWriter;

    public String getDateTimeString()
    {
        //Time
        StringBuilder   strBuilder_curTime = new StringBuilder();
        Calendar        calenar_ = new GregorianCalendar();

        strBuilder_curTime.append(String.format("%d_%d_%d_%d_%d_%d",
                calenar_.get(Calendar.YEAR),
                calenar_.get(Calendar.MONTH)+1,
                calenar_.get(Calendar.DAY_OF_MONTH),
                calenar_.get(Calendar.HOUR_OF_DAY),
                calenar_.get(Calendar.MINUTE),
                calenar_.get(Calendar.SECOND)
        ));

        String  strDateTime =  strBuilder_curTime.toString();

        return strDateTime;
    }

    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.button_Save:
            {
                Button btn = (Button)v;
                //정지 상태였다면...
                if(bRecording==Boolean.FALSE)
                {
                    try
                    {
                        String logPath = Environment.getExternalStorageDirectory().getAbsolutePath()+"/" + getDateTimeString()+".csv";
                        fLogFile        = new File(logPath);
                        fLogFile.createNewFile();
                        fOutStream      = new FileOutputStream(fLogFile);
                        outStreamWriter = new OutputStreamWriter(fOutStream);

                        //KML Header
                        String strKMLHeader = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n "+
                        "<kml xmlns=\"http://www.opengis.net/kml/2.2\"><Document>";
                        outStreamWriter.append(strKMLHeader);

                    }  catch (FileNotFoundException e) {e.printStackTrace();}
                    catch (IOException e) {e.printStackTrace();}

                    btn.setText("Stop Recording");
                    bRecording=Boolean.TRUE;
                }
                //저장 중이었으면...
                else {
                    try
                    {
                        //KML Footer
                        String strKMLFooter = "</Document></kml>";
                        outStreamWriter.append(strKMLFooter);

                        outStreamWriter.close();
                        fOutStream.close();
                    }  catch (FileNotFoundException e) {e.printStackTrace();}
                    catch (IOException e) {e.printStackTrace();}

                    btn.setText("Start Recording");
                    bRecording=Boolean.FALSE;
                }
            }
            break;
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_gps__mornitoring__view);

        locationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
        locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 1000, 1, this);
        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        client = new GoogleApiClient.Builder(this).addApi(AppIndex.API).build();

        bRecording = Boolean.FALSE;

    }

    @Override
    public void onLocationChanged(Location location) {

        TextView textView_Lat = (TextView) findViewById(R.id.textView_Lat);
        TextView textView_Lon = (TextView) findViewById(R.id.textView_Lon);
        TextView textView_Alt = (TextView) findViewById(R.id.textView_Alt);
        TextView textView_Accuracy = (TextView) findViewById(R.id.textView_Accuracy);
        TextView textView_Update = (TextView) findViewById(R.id.textView_Update);

        String strLat = "Lat.: " + location.getLatitude();
        String strLon = "Lon.: " + location.getLongitude();
        String strAlt = "Alt.: " + location.getAltitude();
        String strAccrc = "Accuracy : " + location.getAccuracy();

        //Time
        String strDateTime = getDateTimeString();
        StringBuilder   strBuilder_curTime = new StringBuilder();
        strBuilder_curTime.append(String.format("Updated : %s",strDateTime ));

        textView_Lat.setText(strLat);
        textView_Lon.setText(strLon);
        textView_Alt.setText(strAlt);
        textView_Accuracy.setText(strAccrc);
        textView_Update.setText(strBuilder_curTime);

        if(bRecording)
        {
            StringBuilder   strBuilder_file_log = new StringBuilder();

            /*
            strBuilder_file_log.append(String.format("%s,%f,%f,%f,%f\n",
                    strDateTime,
                    location.getLatitude(),
                    location.getLongitude(),
                    location.getAltitude(),
                    location.getAccuracy()));
                    */
            strBuilder_file_log.append(String.format("<Placemark><description>R %.2f</description><Point><coordinates>%.16f,%.16f,%.4f</coordinates></Point></Placemark>\n",
                    location.getAccuracy(),
                    location.getLongitude(),
                    location.getLatitude(),
                    location.getAltitude()));

            try
            {
                outStreamWriter.append(strBuilder_file_log);
            }  catch (FileNotFoundException e) {e.printStackTrace();}
            catch (IOException e) {e.printStackTrace();}

        }

    }

    @Override
    public void onProviderDisabled(String provider) {
        Intent intent = new Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS);
        startActivity(intent);
        Toast.makeText(getBaseContext(), "Gps is turned off!! ",
                Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onProviderEnabled(String provider) {

        Toast.makeText(getBaseContext(), "Gps is turned on!! ",
                Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onStatusChanged(String provider, int status, Bundle extras) {
    }


    @Override
    public void onStart() {
        super.onStart();

        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        client.connect();
        Action viewAction = Action.newAction(
                Action.TYPE_VIEW, // TODO: choose an action type.
                "GPS_Mornitoring_View Page", // TODO: Define a title for the content shown.
                // TODO: If you have web page content that matches this app activity's content,
                // make sure this auto-generated web page URL is correct.
                // Otherwise, set the URL to null.
                Uri.parse("http://host/path"),
                // TODO: Make sure this auto-generated app URL is correct.
                Uri.parse("android-app://group.gld3d.android.gld3d_gps_logger/http/host/path")
        );
        AppIndex.AppIndexApi.start(client, viewAction);
    }

    @Override
    public void onStop() {
        super.onStop();

        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        Action viewAction = Action.newAction(
                Action.TYPE_VIEW, // TODO: choose an action type.
                "GPS_Mornitoring_View Page", // TODO: Define a title for the content shown.
                // TODO: If you have web page content that matches this app activity's content,
                // make sure this auto-generated web page URL is correct.
                // Otherwise, set the URL to null.
                Uri.parse("http://host/path"),
                // TODO: Make sure this auto-generated app URL is correct.
                Uri.parse("android-app://group.gld3d.android.gld3d_gps_logger/http/host/path")
        );
        AppIndex.AppIndexApi.end(client, viewAction);
        client.disconnect();
    }
}
