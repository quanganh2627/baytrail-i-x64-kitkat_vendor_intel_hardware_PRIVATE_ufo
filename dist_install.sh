#! /bin/bash

# dist_install.sh - Copy binary libraries from repository to their output
# locations (typically under ${ANDROID_PRODUCT_OUT}).  Uncompress as needed.
# If an identical file already exists in output location, do not disturb it.
#
# Args:
# 1. Directory containing input files in locations relative to their eventual
#    locations under ${ANDROID_PRODUCT_OUT}.  If blank, {script_directory}/dist
# 2. Directory under which files will be installed.
#    If blank, defaults to ${ANDROID_PRODUCT_OUT}

set -e
set -u

proc_path="${BASH_SOURCE[0]}"
pnm="${proc_path##*/}"

opt_verbose=1
opt_dry_run=0

if [ -n "${1:-}" ] ; then
    dir_from="${1}"
else
    dir_from=$( dirname "${proc_path}" )
    if [ "${dir_from}" == "." ] ; then
        dir_from="dist"
    else
        dir_from="${dir_from}/dist"
    fi
fi

if [ -n "${2:-}" ] ; then
    dir_to="${2}"
else
    dir_to=${ANDROID_PRODUCT_OUT}
fi

if [ ! -d "${dir_from}" ] ; then
    echo >&2 "${pnm}: Error: Required directory not present: "${dir_from}""
    exit 1
fi

# Does not duplicate symbolic links yet.

dist_list=( $( ( cd "${dir_from}" ; find . -type f -print | sed -e 's%^./%%' ) ) )

for dist_file in "${dist_list[@]:+${dist_list[@]}}" ; do
    if [ "${dir_from}" == "." ] ; then
        path_from="${dist_file}"
    else
        path_from="${dir_from}/${dist_file}"
    fi

    file_ext="${path_from##*.}"
    if [ "${file_ext}" == "${path_from}" ] ; then
        file_ext=""
    fi

    if [ ! -r "${path_from}" ] ; then
        echo >&2 "${pnm}: Error: Input file not found: ${path_from}"
        continue
    fi

    flag_redirect=1
    case "${file_ext}" in
        bz2)
            cpcmd="bzip2 -dc"
            pgm_diff=xzdiff
            ;;
        gz)
            cpcmd="gzip -dc"
            # In case system does not have xzdiff installed.
            pgm_diff=zdiff
            ;;
        xz)
            cpcmd="xz -dc"
            pgm_diff=xzdiff
            ;;
        *)
            cpcmd="cp"
            pgm_diff=diff
            flag_redirect=0
            file_ext=""
            ;;
    esac

    path_to="${dir_to}/${dist_file}"
    if [ -n "${file_ext}" ] ; then
        path_to="${path_to%.*}"
    fi

    # If the file is already there, do not update it unless it is different.
    # This will help to avoid needless rebuilds by users of the libraries.

    # xzdiff recognizes compression types none, xz, lzma, gzip, bzip2, and lzop.
    if [ -e "${path_to}" ] && ${pgm_diff} -q "${path_from}" "${path_to}" >/dev/null ; then
        # Files are the same.  Take no action.
        if [ ${opt_verbose} -ge 1 ] ; then
            echo >&2 "${pnm}: Info: File is unchanged: ${path_from}"
        fi
    else
        path_to_dir=$( dirname "${dir_to}/${dist_file}" )
        if [ ! -d "${path_to_dir}" ] ; then
            if [ ${opt_verbose} -ge 1 ] || [ ${opt_dry_run} -ne 0 ] ; then
                echo >&2 "+ " mkdir -p "${path_to_dir}"
            fi
            if [ ${opt_dry_run} -eq 0 ] ; then
                mkdir -p "${path_to_dir}"
            fi
        fi

        if [ ${flag_redirect} -eq 0 ] ; then
            if [ ${opt_verbose} -ge 1 ] || [ ${opt_dry_run} -ne 0 ] ; then
                echo >&2 "+ " ${cpcmd} "${path_from}" "${path_to}"
            fi
            if [ ${opt_dry_run} -eq 0 ] ; then
                ${cpcmd} "${path_from}" "${path_to}"
            fi
        else
            if [ ${opt_verbose} -ge 1 ] || [ ${opt_dry_run} -ne 0 ] ; then
                echo >&2 "+ " ${cpcmd} "${path_from}" ">${path_to}"
            fi
            if [ ${opt_dry_run} -eq 0 ] ; then
                ${cpcmd} "${path_from}" >"${path_to}"
            fi
        fi
    fi
done
